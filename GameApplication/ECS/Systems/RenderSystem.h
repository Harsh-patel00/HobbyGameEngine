//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "EventManager.h"
#include "GMath/Vector.h"
#include "GGraphics/Transformations.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"

using Transform = Components::Transform;
using Camera = Components::Camera;
using MeshComponent = Components::MeshComponent;

class RenderSystem : ECS::System
{
	private:
		GEngine::EngineWindow *pWindow{};
		Camera *_pSceneCamera{};
	public:
		explicit RenderSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world) override { }

		void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window)
		{
			// Calling base OnCreate (As of now it does nothing)
			ECS::System::OnCreate(world);

			pWindow = window;

			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, Camera>())
			{
				auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
				_pSceneCamera = world->GetEcsManager()->GetComponent<Camera>(entId);
				_pSceneCamera->origin = transform->position;
			}

			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
			{
				auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
				auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);

				ProcessMesh(meshComp->mesh, *transform);
			}
		}

		void OnUpdate(double dt, GEngine::GameWorld *world) override { }

		void OnUpdate(double dt, GEngine::GameWorld *world, GEngine::EngineWindow *window) { }

		static void DrawFullScreenTriangle(GEngine::EngineWindow *window)
		{
			GGraphics::Primitives2d::Triangle t
					{
							{((float) window->GetWidth() / 2) - 100, ((float) window->GetHeight() / 2) - 100, 0},
							{(float) window->GetWidth() / 2,         ((float) window->GetHeight() / 2) + 100, 0},
							{((float) window->GetWidth() / 2) + 100, ((float) window->GetHeight() / 2) - 100, 0}
					};

			t.Draw(window, GGraphics::Color(GGraphics::ColorEnum::CYAN));
		}

		void ProcessMesh(const GGraphics::Mesh& mesh, const Transform &transform)
		{
			// Convert from Local to World Position
			// Convert from World to View
			// Convert from View to Projection (-1, 1)
			// Convert from Projection to Window

			GGraphics::Mesh meshCopy = mesh;

			std::cout << "Original Mesh :: \n";

			for (auto tri : mesh.GetTriangles())
			{
				tri.Print();
			}

			ConvertLocalToWorld(meshCopy, transform);
			ConvertWorldToView(meshCopy);

			std::cout << "Transformed Mesh :: \n";

			for (auto tri : meshCopy.GetTriangles())
			{
				tri.Print();
			}

		}

		void ConvertLocalToWorld(GGraphics::Mesh &mesh, const Transform &transform)
		{
			std::cout << "Converting from local to world!...\n";

			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};

			GMath::Mat4f T = GGraphics::Transformation::GetTranslationMatrix(transform.position);
			GMath::Mat4f R = GGraphics::Transformation::GetRotationMatrix(transform.rotation);
			GMath::Mat4f S = GGraphics::Transformation::GetScaleMatrix(transform.scale);

			// Multiplication in order
			// 1. Scale
			// 2. Rotate
			// 3. Translate
			GMath::Mat4f matL2W =  S * R * T;

			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;

				// For each point in triangle
				for(GMath::Point3f &point : transformedTri.points)
				{
					// Apply Transformations
					point = GMath::Mat4f::Matrix4Vec3Multiplication(point, matL2W);
				}

				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

		void ConvertWorldToView(GGraphics::Mesh &mesh)
		{
			std::vector<GGraphics::Primitives2d::Triangle> transformedTris{};
			for (auto tri : mesh.GetTriangles())
			{
				GGraphics::Primitives2d::Triangle transformedTri = tri;
				for(GMath::Point3f &point : transformedTri.points)
				{
					GMath::Mat4f w2v = GGraphics::Transformation::GetWorldToViewMatrix
							(_pSceneCamera->origin, _pSceneCamera->lookAt, _pSceneCamera->upDirection);

					point = GMath::Mat4f::Matrix4Vec3Multiplication(point, w2v);
				}
				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

};

#endif //GAMEENGINE_RENDERSYSTEM_H
