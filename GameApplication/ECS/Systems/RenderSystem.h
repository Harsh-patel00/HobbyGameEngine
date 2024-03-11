//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "Utilities/EngineEventManager.h"
#include "GGraphics/Transformations.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/Camera.h"


using Transform = Components::Transform;
using Camera = Components::Camera;
using MeshComponent = Components::MeshComponent;

using namespace GMath;

class RenderSystem : ECS::System
{
private:
	GEngine::EngineWindow *pWindow{};


	Camera _sceneCamera{};


	float rotation{}, speed = 50;


public:
	explicit RenderSystem( const std::string &name ) : System(name)
	{}

public:
	void OnCreate( GEngine::GameWorld *world, GEngine::EngineWindow *window ) override
	{
		pWindow = window;

		Events::EngineEventManager::WindowResized.AddListener([this]()
																  {
																  SetupSceneCamera(_sceneCamera);
																  });

		//for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
		//{
		//	auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
		//	auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);
		//
		//	ProcessMesh(meshComp->mesh, *transform);
		//}
	}

	void OnUpdate( double dt, GEngine::GameWorld *world ) override
	{
		if ( _sceneCamera.showViewportBG )
		{
			DrawViewportBG();
		}

		rotation += (float) dt * speed;

		if ( rotation > 359 )
		{
			rotation = 0;
		}

		int        entCount = 1;
		for ( auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>() )
		{
			auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
			auto meshComp  = world->GetEcsManager()->GetComponent<MeshComponent>(entId);
			Vec3f rotVec;

			//entCount = 4;

			if ( entCount % 2 == 0 )
			{
				rotVec = Vec3f(0, rotation, 0);
			}
			else if ( entCount % 3 == 0 )
			{
				rotVec = Vec3f(0, 0, rotation);
			}
			else
			{
				rotVec = Vec3f(rotation, 0, 0);
			}

			if ( entCount == 4 )
			{
				rotVec = Vec3f(rotation, rotation, rotation);
			}

			world->GetEcsManager()
				 ->SetComponentValue<Transform>({transform->position, transform->rotation /*rotVec*/,
												 transform->scale}, entId);

			std::unique_ptr<GGraphics::Mesh> meshCopy = std::make_unique<GGraphics::Mesh>(meshComp->mesh);

			/*{
				std::cout << "Original Mesh :: \n";

				for (auto tri: meshComp->mesh.GetTriangles())
				{
					tri.Print();
				}
			}*/

			ProcessMesh(*meshCopy, *transform);

			/*{
				std::cout << "Transformed Mesh :: \n";

				for (auto tri: meshCopy->GetTriangles())
				{
					tri.Print();
				}
			}*/

			entCount++;
		}
	}

	// For debugging only
	void DrawViewportBG()
	{

		for ( int x = _sceneCamera.viewport.startX;
			  x <= (_sceneCamera.viewport.startX + _sceneCamera.viewport.width);
			  x++ )
		{
			for ( int y = _sceneCamera.viewport.startY;
				  y <= (_sceneCamera.viewport.startY + _sceneCamera.viewport.height);
				  y++ )
			{
				pWindow->DrawPixel(x, y, _sceneCamera.cameraBgColor);
			}
		}
	}

	void ProcessMesh( GGraphics::Mesh &mesh, const Transform &transform )
	{
		// Convert from Local to World Position
		// Convert from World to View
		// Convert from View to Projection (Camera Frustum is CVV here)
		// Convert from Projection to Window (CVV is a rectangle which maps to screen) ([-1, 1] -> [screen size])

		// Part of Vertex Shader
		ConvertLocalToWorld(mesh, transform);
		ConvertWorldToView(mesh);

		// Part of Geometry Shader
		// TODO: Perform cullling operations before projection
		//CullBackfaces(mesh);
		ConvertViewToProjection(mesh);
		// TODO: Perform clipping operations after projection

		// Viewport is also called CVV
		// Rasterize

		ConvertProjectionToViewport(mesh);

		// Part of Fragment Shader
		mesh.Draw(pWindow, GGraphics::Color(GGraphics::ColorEnum::GREEN));
	}

	void ConvertLocalToWorld( GGraphics::Mesh &mesh, const Transform &transform )
	{
		Mat4f T = GGraphics::Transformation::GetTranslationMatrix(transform.position);
		Mat4f R = GGraphics::Transformation::GetRotationMatrix(transform.rotation);
		Mat4f S = GGraphics::Transformation::GetScaleMatrix(transform.scale);

		// Multiplication in order
		// 1. Scale (S)
		// 2. Rotate (R)
		// 3. Translate (T)
		Mat4f matL2W = T * R * S;

		//			std::cout << "matL2W Mat :: " << matL2W << "\n";

		auto modifiedVerts = mesh.GetVertices();
		// For each point in mesh
		for ( Point3f &point : modifiedVerts )
		{
			// Apply Transformations
			point = matL2W * point;
		}
		mesh.SetVertices(modifiedVerts);
	}

	void ConvertWorldToView( GGraphics::Mesh &mesh )
	{
		Mat4f w2v = GGraphics::Transformation::GetWorldToViewMatrix(_sceneCamera.origin, _sceneCamera.lookAt, _sceneCamera.upDirection);

		//			std::cout << "w2v Mat :: " << w2v << "\n";

		auto modifiedVerts = mesh.GetVertices();

		for ( Point3f &point : modifiedVerts )
		{
			point = w2v * point;
		}

		mesh.SetVertices(modifiedVerts);
	}

	void ConvertViewToProjection( GGraphics::Mesh &mesh )
	{
		//			std::cout << "View >> Proj\n";

		Mat4f projectionMatrix = GGraphics::Transformation::GetProjectionMatrix(_sceneCamera);

		//			std::cout << "v2P Mat :: " << projectionMatrix << "\n";
		auto          modifiedVerts = mesh.GetVertices();
		for ( Point3f &point : modifiedVerts )
		{
			point = projectionMatrix * point;
			//std::cout << "Projected Point :: " << point << '\n';
		}

		mesh.SetVertices(modifiedVerts);
	}

	void ConvertProjectionToViewport( GGraphics::Mesh &mesh )
	{
		//			std::cout << "Proj >> Viewport \n";

		auto verts = mesh.GetVertices();

		for ( Point3f &point : verts )
		{
			ConvertPointToScreenSpace(point);
		}

		mesh.SetVertices(verts);
	}

	void SetupSceneCamera( Camera &camera )
	{
		camera.origin      = {0, 0, -10};
		camera.lookAt      = Vec3f(0, 0, 1);
		camera.upDirection = Vec3f(0, 1, 0);

		camera.type = Components::CameraType::PERSPECTIVE;

		auto viewportWidth  = pWindow->GetWidth();
		auto viewportHeight = pWindow->GetHeight();

		camera.viewport = {0, 0, viewportWidth, viewportHeight};
		camera.cvv      = {(float) camera.viewport.width, (float) camera.viewport.height, 5, 15};

		camera.size = 1;
		camera.fov  = 60;

		// TODO: Look into this...
		//  Changing this to true, causes heavy performance penalty
		camera.showViewportBG = false;
		camera.cameraBgColor  = GGraphics::Color(GGraphics::ColorEnum::RED);
	}

	void ConvertPointToScreenSpace(Point3f &point) const
	{
		//Point3f convertedPoint = point;

		float xScreen = (point.x + 1.f) * 0.5f * (float) _sceneCamera.viewport.width;
		float yScreen = (point.y + 1.f) * 0.5f * (float) _sceneCamera.viewport.height;


		// convert to raster space and mark the position of the vertex in the image with a simple dot
		point.x = xScreen + (float) _sceneCamera.viewport.startX;
		point.y = yScreen + (float) _sceneCamera.viewport.startY;
	}

};

#endif //GAMEENGINE_RENDERSYSTEM_H
