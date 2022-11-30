//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "EventManager.h"
#include "GMath/Vector.h"
#include "GGraphics/ModellingTransformation.h"
#include "GGraphics/ViewingTransformation.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"

class RenderSystem : ECS::System
{
	private:
		GGraphics::Camera _sceneCamera{};
		GEngine::EngineWindow *pWindow{};
	public:
		explicit RenderSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world) override { }

		void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window)
		{
			// Calling base OnCreate (As of now it does nothing)
			ECS::System::OnCreate(world);

			pWindow = window;

			_sceneCamera = {0.1f, 1000.f, 60.f, (float) window->GetWidth() / (float) window->GetHeight()};

			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
			{
				auto transform = world->GetEcsManager()->GetComponent<Transform>(entId);
				auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);
				ProcessMesh(meshComp->mesh, *transform);
			}
		}

		void OnUpdate(double dt, GEngine::GameWorld *world) override { }

		void OnUpdate(double dt, GEngine::GameWorld *world, GEngine::EngineWindow *window) { }

		void DrawFullScreenTriangle(GEngine::EngineWindow *window)
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
					// Get the translation matrix for the point
					// Ti = Translation to origin
					GMath::Mat4f Ti = GGraphics::Transformation::GetTranslationMatrix(point * -1);
					// Translate it to the origin
					GMath::Point3f translatedPoint = GMath::Mat4f::Matrix4Vec3Multiplication(point, Ti);
					// Apply Transformations
					translatedPoint = GMath::Mat4f::Matrix4Vec3Multiplication(translatedPoint, matL2W);
					// Translate back to the original place
					// To = Translation to original place
					GMath::Mat4f To = GGraphics::Transformation::GetTranslationMatrix(point);
					point = GMath::Mat4f::Matrix4Vec3Multiplication(translatedPoint, To);
				}

				transformedTris.push_back(transformedTri);
			}
			mesh.SetTriangles(transformedTris);
		}

};

#endif //GAMEENGINE_RENDERSYSTEM_H
