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
				 ->SetComponentValue<Transform>({transform->position, /*transform->rotation*/ rotVec,
												 transform->scale}, entId);

			// Stack-local copy — avoids heap allocation; only vertices are transformed
			GGraphics::Mesh meshCopy(meshComp->mesh);
			ProcessMesh(meshCopy, *transform);

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
		// Build composite matrix: Local → World → View → Projection
		// This is a single matrix that transforms vertices from local space to clip space
		Mat4f T = GGraphics::Transformation::GetTranslationMatrix(transform.position);
		Mat4f R = GGraphics::Transformation::GetRotationMatrix(transform.rotation);
		Mat4f S = GGraphics::Transformation::GetScaleMatrix(transform.scale);
		Mat4f modelMatrix = T * R * S;

		Mat4f viewMatrix = GGraphics::Transformation::GetWorldToViewMatrix(
			_sceneCamera.origin, _sceneCamera.lookAt, _sceneCamera.upDirection);

		Mat4f projMatrix = GGraphics::Transformation::GetProjectionMatrix(_sceneCamera);

		// TODO: Perform backface culling in view space (before projection)
		// TODO: Perform clipping in clip space (after projection, before viewport)

		// Single-pass vertex transform: local → world → view → projection → screen
		// Only one call to SetVertices — only one UpdateTriVertices
		auto verts = mesh.GetVertices();
		for ( Point3f &point : verts )
		{
			// Model → View (affine, w stays 1 — no w-divide in Mat4f*Point3f)
			point = viewMatrix * (modelMatrix * point);

			// View → Clip → NDC (perspective divide happens inside Mat4f*Point3f when w != 1)
			point = projMatrix * point;

			// NDC → Screen
			ConvertPointToScreenSpace(point);
		}
		mesh.SetVertices(verts);

		// Rasterize
		mesh.Draw(pWindow, GGraphics::Color(GGraphics::ColorEnum::GREEN));
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
