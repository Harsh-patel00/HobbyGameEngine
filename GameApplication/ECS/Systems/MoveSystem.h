//
// Created by Harsh on 29-01-2022.
//

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/InputCon.h"

#include "EventManager.h"

#ifndef GAMEENGINE_MOVESYSTEM_H
#define GAMEENGINE_MOVESYSTEM_H

class MoveSystem : ECS::System
{
	public:
		explicit MoveSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world) override
		{
			ECS::System::OnCreate(world);
//			std::cout << "Overridden OnCreate...\n";

//			EventManager::RightKeyPressed.AddListener(MoveRight);
//			EventManager::LeftKeyPressed.AddListener(MoveLeft);
		}

		void OnUpdate(float dt, GEngine::GameWorld *world) override
		{
			for (auto ent : world->GetEcsManager()->EntitiesWithComponents<Transform, MeshComponent, InputControl>())
			{
				auto tc = world->GetEcsManager()->GetComponent<Transform>(ent);
				auto ic = world->GetEcsManager()->GetComponent<InputControl>(ent);

				if(ic->right)
				{
					tc->position.x += 10;
				}

				if(ic->left)
				{
					tc->position.x -= 10;
				}

				// Set the updated position
				world->GetEcsManager()->SetComponentValue<Transform>({tc->position}, ent);
				// Reset the values of the input so that the above conditions are always false
				world->GetEcsManager()->SetComponentValue<InputControl>({}, ent);
			}

		}
};

#endif //GAMEENGINE_MOVESYSTEM_H
