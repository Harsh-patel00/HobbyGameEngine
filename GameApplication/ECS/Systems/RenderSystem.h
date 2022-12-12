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
		explicit RenderSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window) override
		{
			pWindow = window;

			Events::EngineEventManager::WindowResized.AddListener([this](){
				SetupSceneCamera(_sceneCamera);
			});

//			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
//			{
//				auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
//				auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);
//
//				ProcessMesh(meshComp->mesh, *transform);
//			}
		}

		void OnUpdate(double dt, GEngine::GameWorld *world) override
		{
			rotation += (float) dt * speed;

			if(rotation > 359)
				rotation = 0;

			int entCount = 1;
			for (auto entId: world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
			{
				auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
				auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);

				Vec3f rotVec;

				if(entCount % 2 == 0)
				{
					rotVec = Vec3f(0, rotation, 0);
				}
				else if(entCount % 3 == 0)
				{
					rotVec = Vec3f(0, 0, rotation);
				}
				else
				{
					rotVec = Vec3f(rotation, 0, 0);
				}

				if(entCount == 4)
				{
					rotVec = Vec3f(rotation, rotation, rotation);
				}

				world->GetEcsManager()->SetComponentValue<Transform>(
						{transform->position,
						 rotVec,
						 transform->scale}, entId);

				ProcessMesh(meshComp->mesh, *transform);

				entCount++;
			}
		}

		void ProcessMesh(const GGraphics::Mesh& mesh, const Transform &transform)
		{
			// Convert from Local to World Position
			// Convert from World to View
			// Convert from View to Projection (-1, 1)
			// Convert from Projection to Window

			GGraphics::Mesh meshCopy = mesh;

//			std::cout << "Original Mesh :: \n";

			for (auto tri : mesh.GetTriangles())
			{
//				tri.Print();
			}

			ConvertLocalToWorld(meshCopy, transform);
			ConvertWorldToView(meshCopy);
			ConvertViewToProjection(meshCopy);
			ConvertProjectionToViewport(meshCopy);

//			std::cout << "Transformed Mesh :: \n";

			for (auto tri : meshCopy.GetTriangles())
			{
//				tri.Print();
				tri.Draw(pWindow, GGraphics::Color(GGraphics::ColorEnum::GREEN));
			}

		}

		void ConvertLocalToWorld(GGraphics::Mesh &mesh, const Transform &transform)
		{
			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};

			Mat4f T = GGraphics::Transformation::GetTranslationMatrix(transform.position);
			Mat4f R = GGraphics::Transformation::GetRotationMatrix(transform.rotation);
			Mat4f S = GGraphics::Transformation::GetScaleMatrix(transform.scale);

			// Multiplication in order
			// 1. Scale (S)
			// 2. Rotate (R)
			// 3. Translate (T)
			Mat4f matL2W =  T * R * S;

//			std::cout << "matL2W Mat :: " << matL2W << "\n";

			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;

				// For each point in triangle
				for(Point3f &point : transformedTri.points)
				{
					// Apply Transformations
					point = matL2W * point;
				}

				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

		void ConvertWorldToView(GGraphics::Mesh &mesh)
		{
			Mat4f w2v = GGraphics::Transformation::GetWorldToViewMatrix
					(_sceneCamera.origin, _sceneCamera.lookAt, _sceneCamera.upDirection);

//			std::cout << "w2v Mat :: " << w2v << "\n";

			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};
			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;
				for(Point3f &point : transformedTri.points)
				{
					point = w2v * point;
				}
				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

		void ConvertViewToProjection(GGraphics::Mesh &mesh)
		{
//			std::cout << "View >> Proj\n";
			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};

			Mat4f projectionMatrix = GGraphics::Transformation::GetProjectionMatrix(_sceneCamera);

//			std::cout << "v2P Mat :: " << projectionMatrix << "\n";

			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;
				for (Point3f &point: transformedTri.points)
				{
					point = projectionMatrix * point;
				}
				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

		void ConvertProjectionToViewport(GGraphics::Mesh &mesh)
		{
//			std::cout << "Proj >> Viewport \n";
			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};
			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;
				for (Point3f &point: transformedTri.points)
				{
					// Discard any point outside cvv
					if (point.x < -1 || point.x > 1 || point.y < -1 || point.y > 1) continue;

					uint32_t xScreen = (point.x + 1) * 0.5 * _sceneCamera.viewport.width;
					uint32_t yScreen = (point.y + 1) * 0.5 * _sceneCamera.viewport.height;

//					if(xScreen <= 0 || yScreen <= 0)
//					{
//						std::cout << "XS :: " << xScreen << ", YS :: " << yScreen << "\n";
//					}

					// convert to raster space and mark the position of the vertex in the image with a simple dot
					point.x = xScreen;
					point.y = yScreen;


				}
				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

		void SetupSceneCamera(Camera &camera)
		{
			camera.origin = {0, 5, -10};
			camera.lookAt = Vec3f(0, 0, 0);
			camera.upDirection = Vec3f(0, 1, 0);

			camera.type = Components::CameraType::PERSPECTIVE;

			camera.viewport = {0, 0, pWindow->GetWidth(), pWindow->GetHeight()};
			camera.cvv = {(float)camera.viewport.width, (float)camera.viewport.height, 5, 15};

			camera.size = 1;
			camera.fov = 60;
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
