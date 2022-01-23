//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "graphics.h"

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/Renderer.h"

class RenderSystem : ECS::System
{
	public:
		explicit RenderSystem(const std::string &name) : System(name)
		{
			initwindow(800, 600);
		}

	public:
		void OnUpdate(float dt, ECS::EcsManager *em) override
		{
			std::cout << "dt : " << dt << "\n";
			for (auto entId : em->EntitiesWithComponents<Renderer>())
			{
				std::cout << "Entities with renderer : " << em->GetEntityName(entId) << "\n";
			}
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
