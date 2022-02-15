//
// Created by Harsh on 29-01-2022.
//

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"
#include "ECS/Components/InputCon.h"

#include "EventManager.h"

#ifndef GAMEENGINE_MOVESYSTEM_H
#define GAMEENGINE_MOVESYSTEM_H

class MoveSystem : ECS::System
{
	public:
		explicit MoveSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(ECS::EcsManager *em) override
		{
			ECS::System::OnCreate(em);
//			std::cout << "Overridden OnCreate...\n";

//			EventManager::RightKeyPressed.AddListener(MoveRight);
//			EventManager::LeftKeyPressed.AddListener(MoveLeft);
		}

		void OnUpdate(float dt, ECS::EcsManager *em) override
		{
			for (auto ent : em->EntitiesWithComponents<Transform, Renderer, InputControl>())
			{
				auto tc = em->GetComponent<Transform>(ent);
				auto ic = em->GetComponent<InputControl>(ent);

				if(ic->right)
				{
					tc->position.x += 10;
				}

				if(ic->left)
				{
					tc->position.x -= 10;
				}

				// Set the updated position
				em->SetComponentValue<Transform>({tc->position}, ent);
				// Reset the values of the input so that the above conditions are always false
				em->SetComponentValue<InputControl>({}, ent);
			}

		}
};

#endif //GAMEENGINE_MOVESYSTEM_H
