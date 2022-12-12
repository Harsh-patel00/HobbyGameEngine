//
// Created by Harsh on 29-01-2022.
//

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/InputCon.h"


#ifndef GAMEENGINE_MOVESYSTEM_H
#define GAMEENGINE_MOVESYSTEM_H

class MoveSystem : ECS::System
{
	public:
		float speed = 5.f;

	public:
		explicit MoveSystem(const std::string &name) : System(name){}

	public:
		void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window) override {}

		void OnUpdate(double dt, GEngine::GameWorld *world) override
		{
			for (auto ent : world->GetEcsManager()->EntitiesWithComponents<Transform, Components::InputControl>())
			{
				auto tc = world->GetEcsManager()->GetComponent<Transform>(ent);
				auto ic = world->GetEcsManager()->GetComponent<Components::InputControl>(ent);

				if(ic->right)
				{
					tc->position.x += (1.5f * dt * speed);
				}

				if(ic->left)
				{
					tc->position.x -= (1.5f * dt * speed);
				}

				if(ic->up)
				{
					tc->position.z += (1.5f * dt * speed);
				}

				if(ic->down)
				{
					tc->position.z -= (1.5f * dt * speed);
				}

				// Set the updated position
				world->GetEcsManager()->SetComponentValue<Transform>({tc->position}, ent);
				// Reset the values of the input so that the above conditions are always false
				world->GetEcsManager()->SetComponentValue<Components::InputControl>({}, ent);
			}

		}
};

#endif //GAMEENGINE_MOVESYSTEM_H
