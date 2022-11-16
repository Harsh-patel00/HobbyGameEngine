//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/GameObject.h"
#include "GMath/MVector.h"
#include "EventManager.h"

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
		void OnUpdate(float dt, GEngine::GameWorld *world) override
		{
			// Looping through all entities with GameObject component
			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<GameObject>())
			{
				auto go = world->GetEcsManager()->GetComponent<GameObject>(entId);
			}

		}

		void OnUpdate(float dt, GEngine::GameWorld *world, GEngine::EngineWindow *window)
		{
			OnUpdate(dt, world);
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
