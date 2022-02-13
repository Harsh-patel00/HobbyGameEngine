//
// Created by Harsh on 29-01-2022.
//

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"

#include "EventManager.h"

#ifndef GAMEENGINE_MOVESYSTEM_H
#define GAMEENGINE_MOVESYSTEM_H

void HandleRightKey(int);
void HandleLeftKey(int);

void HandleRightKey(int x)
{
	std::cout << "Right key pressed!\nValue of x : " << x << "\nFrom move system\n";

	EventManager::LeftKeyPressed.RemoveListener(HandleLeftKey);
}

void HandleLeftKey(int x)
{
	std::cout << "Left key pressed!\nValue of x : " << x << "\nFrom move system\n";
}

class MoveSystem : ECS::System
{
	public:
		explicit MoveSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(ECS::EcsManager *em) override
		{
			ECS::System::OnCreate(em);
//			std::cout << "Overridden OnCreate...\n";

			EventManager::RightKeyPressed.AddListener(HandleRightKey);
			EventManager::LeftKeyPressed.AddListener(HandleLeftKey);
		}

		void OnUpdate(float dt, ECS::EcsManager *em) override
		{
			for (auto ent : em->EntitiesWithComponents<Transform, Renderer>())
			{
				auto tc = em->GetComponent<Transform>(ent);
				tc->position.y += 10 * dt;
				em->SetComponentValue<Transform>({tc->position}, ent);
			}
		}
};

#endif //GAMEENGINE_MOVESYSTEM_H
