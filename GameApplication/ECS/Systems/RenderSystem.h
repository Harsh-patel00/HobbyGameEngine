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

		void OnUpdate(float dt, GEngine::GameWorld *world) override { }

		void OnUpdate(float dt, GEngine::GameWorld *world, GEngine::EngineWindow *window)
		{
			// Looping through all entities with GameObject component
			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<GameObject>())
			{
				auto go = world->GetEcsManager()->GetComponent<GameObject>(entId);

				GGraphics::GShapes shapeClass{};
				shapeClass.SetLine(go->transform.position, {10, 10, 0});

				go->renderer.graphic.SetBrushColor(GGraphics::GColor(GGraphics::Color::YELLOW));
				go->renderer.graphic.Draw(shapeClass, window);
			}
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
