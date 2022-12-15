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

				auto *meshCopy = new GGraphics::Mesh(meshComp->mesh, true);

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

					for (auto tri: meshComp->mesh.GetTriangles())
					{
						tri.Print();
					}
				}*/

				entCount++;
			}
		}

		void ProcessMesh(GGraphics::Mesh& mesh, const Transform &transform)
		{
			// Convert from Local to World Position
			// Convert from World to View
			// Convert from View to Projection (-1, 1)
			// Convert from Projection to Window

			ConvertLocalToWorld(mesh, transform);
			ConvertWorldToView(mesh);
			ConvertViewToProjection(mesh);
			// TODO: Perform clipping operations after projection
			ConvertProjectionToViewport(mesh);

			mesh.Draw(pWindow, GGraphics::Color(GGraphics::ColorEnum::GREEN));

		}

		void ConvertLocalToWorld(GGraphics::Mesh &mesh, const Transform &transform)
		{
			Mat4f T = GGraphics::Transformation::GetTranslationMatrix(transform.position);
			Mat4f R = GGraphics::Transformation::GetRotationMatrix(transform.rotation);
			Mat4f S = GGraphics::Transformation::GetScaleMatrix(transform.scale);

			// Multiplication in order
			// 1. Scale (S)
			// 2. Rotate (R)
			// 3. Translate (T)
			Mat4f matL2W =  T * R * S;

//			std::cout << "matL2W Mat :: " << matL2W << "\n";

			// For each point in mesh
			for(Point3f &point : *mesh.GetVertices())
			{
				// Apply Transformations
				point = matL2W * point;
			}
		}

		void ConvertWorldToView(GGraphics::Mesh &mesh)
		{
			Mat4f w2v = GGraphics::Transformation::GetWorldToViewMatrix
					(_sceneCamera.origin, _sceneCamera.lookAt, _sceneCamera.upDirection);

//			std::cout << "w2v Mat :: " << w2v << "\n";

			for(Point3f &point : *mesh.GetVertices())
			{
				point = w2v * point;
			}
		}

		void ConvertViewToProjection(GGraphics::Mesh &mesh)
		{
//			std::cout << "View >> Proj\n";

			Mat4f projectionMatrix = GGraphics::Transformation::GetProjectionMatrix(_sceneCamera);

//			std::cout << "v2P Mat :: " << projectionMatrix << "\n";

			for(Point3f &point : *mesh.GetVertices())
			{
					point = projectionMatrix * point;

			}
		}

		void ConvertProjectionToViewport(GGraphics::Mesh &mesh)
		{
//			std::cout << "Proj >> Viewport \n";

			auto meshIndices = mesh.GetIndices();
			std::vector<Point3f> *meshVertices = mesh.GetVertices();

			// Clip lines
			GGraphics::Primitives2d::Triangle tri{};
			// for each index in indices
			for(int i = 0; i < meshIndices.size(); i++)
			{
				tri.points[i%3] = (*meshVertices)[meshIndices[i]];

				if(i%3 == 2)
				{
//					for (int j = 0; j < 3; ++j)
//					{
//						ClipLine(-1, -1, 1, 1, tri.points[j%3].x, tri.points[j%3].y, tri.points[(j+1)%3].x, tri.points[(j+1)%3].y);
//						(*meshVertices)[meshIndices[i - j]] = tri.points[(i - j)%3];
//					}

					ClipLine(-1, -1, 1, 1, tri.points[(i - 2)%3].x, tri.points[(i - 2)%3].y, tri.points[(i - 1)%3].x, tri.points[(i - 1)%3].y);
					ClipLine(-1, -1, 1, 1, tri.points[(i - 1)%3].x, tri.points[(i - 1)%3].y, tri.points[(i-0)%3].x, tri.points[(i-0)%3].y);
					ClipLine(-1, -1, 1, 1, tri.points[(i - 0)%3].x, tri.points[(i-0)%3].y, tri.points[(i - 2)%3].x, tri.points[(i - 2)%3].y);

					(*meshVertices)[meshIndices[i - 2]] = tri.points[(i - 2)%3];
					(*meshVertices)[meshIndices[i - 1]] = tri.points[(i - 1)%3];
					(*meshVertices)[meshIndices[i - 0]] = tri.points[(i - 0)%3];
				}
			}

			for(Point3f &point : *mesh.GetVertices())
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
//			}
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

		float maxi(const float arr[],int n) {
			float m = 0;
			for (int i = 0; i < n; ++i)
				if (m < arr[i])
					m = arr[i];
			return m;
		}

		float mini(const float arr[], int n) {
			float m = 1;
			for (int i = 0; i < n; ++i)
				if (m > arr[i])
					m = arr[i];
			return m;
		}

		// Liang–Barsky line clipping algorithm [Ref: https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorithm]
		void ClipLine(float xmin, float ymin, float xmax, float ymax, float &x1, float &y1, float &x2, float &y2)
		{
			// defining variables
			float p1 = -(x2 - x1);
			float p2 = -p1;
			float p3 = -(y2 - y1);
			float p4 = -p3;

			float q1 = x1 - xmin;
			float q2 = xmax - x1;
			float q3 = y1 - ymin;
			float q4 = ymax - y1;

			float posarr[5], negarr[5];
			int posind = 1, negind = 1;
			posarr[0] = 1;
			negarr[0] = 0;

			if((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0))
			{
//				std::cout << "Line is parallel to clipping window!\n";
				return;
			}
			if(p1 != 0)
			{
				float r1 = q1 / p1;
				float r2 = q2 / p2;
				if(p1 < 0)
				{
					negarr[negind++] = r1; // for negative p1, add it to negative array
					posarr[posind++] = r2; // and add p2 to positive array
				}
				else
				{
					negarr[negind++] = r2;
					posarr[posind++] = r1;
				}
			}
			if(p3 != 0)
			{
				float r3 = q3 / p3;
				float r4 = q4 / p4;
				if(p3 < 0)
				{
					negarr[negind++] = r3;
					posarr[posind++] = r4;
				}
				else
				{
					negarr[negind++] = r4;
					posarr[posind++] = r3;
				}
			}

			float xn1, yn1, xn2, yn2;
			float rn1, rn2;
			rn1 = maxi(negarr, negind); // maximum of negative array
			rn2 = mini(posarr, posind); // minimum of positive array

			if(rn1 > rn2)
			{ // reject
//				std::cout << "Line is outside the clipping window!\n";
				return;
			}

			xn1 = x1 + p2 * rn1;
			yn1 = y1 + p4 * rn1; // computing new points

			xn2 = x1 + p2 * rn2;
			yn2 = y1 + p4 * rn2;

			x1 = xn1;
			y1 = yn1;
			x2 = xn2;
			y2 = yn2;

//			line(xn1, yn1, xn2, yn2); // the drawing the new line

			// line(x1, y1, xn1, yn1); // 1st Discarded line
			// line(x2, y2, xn2, yn2); // 2nd Discarded line
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
