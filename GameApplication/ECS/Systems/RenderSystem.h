//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "EventManager.h"
#include "GMath/Vector.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"

class RenderSystem : ECS::System
{
	public:
		explicit RenderSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world) override
		{
			// Calling base OnCreate (As of now it does nothing)
			ECS::System::OnCreate(world);
			// std::cout << "Overridden OnCreate...\n";
		}

		void OnUpdate(float dt, GEngine::GameWorld *world) override { }

		void OnUpdate(float dt, GEngine::GameWorld *world, GEngine::EngineWindow *window)
		{

			DrawFullScreenTriangle(window);

			// Looping through all entities with GameObject component
			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent>())
			{
				auto go = world->GetEcsManager()->GetComponent<Transform>(entId);
				auto meshComp = world->GetEcsManager()->GetComponent<MeshComponent>(entId);
//				meshComp->mesh.Draw(window, GGraphics::Color(GGraphics::ColorEnum::RED));
			}
		}

		void DrawFullScreenTriangle(GEngine::EngineWindow *window) const
		{
			GGraphics::Primitives2d::Triangle t
			{
				{0, 0, 0},
				{static_cast<float>(window->GetWidth()/2), static_cast<float>(window->GetHeight()), 0},
				{static_cast<float>(window->GetWidth()), 0, 0}
			};

			t.Draw(window, GGraphics::Color(GGraphics::ColorEnum::CYAN));
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
