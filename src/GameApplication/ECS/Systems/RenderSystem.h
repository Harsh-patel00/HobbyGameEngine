//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "graphics.h"

#include "GEngine/EcsCore/System.h"

#include "GGraphics/GWindow/Window.h"

#include "ECS/Components/Renderer.h"

class RenderSystem : ECS::System
{
	private:
		GGraphics::Window window{800, 600, "My Window"};

	public:
		explicit RenderSystem(const std::string &name) : System(name)
		{
			window.SetActive();
		}

	private:
		void SwapBuffers()
		{
			// Double Buffering
			setactivepage(getvisualpage());
			setvisualpage(!getactivepage());
			clearviewport();
		}

	public:
		void OnCreate(GEngine::GameWorld *world) override
		{
			// Calling base OnCreate (As of now it does nothing)
			ECS::System::OnCreate(world);
//			std::cout << "Overridden OnCreate...\n";
		}

		void OnUpdate(float dt, GEngine::GameWorld *world) override
		{
			// Looping through all entities with Transform and Render component
			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<Renderer, Transform>())
			{
				auto rc = world->GetEcsManager()->GetComponent<Renderer>(entId);
				auto tc = world->GetEcsManager()->GetComponent<Transform>(entId);

				switch (rc->drawShape)
				{
					case Shape::Circle:
						circle(tc->position.x, tc->position.y, rc->radius);
						break;
					case Shape::Square:
						rectangle(tc->position.x - (rc->square.dims.x / 2.f),
								  tc->position.y - (rc->square.dims.y / 2.f),
								  tc->position.x + (rc->square.dims.x / 2.f),
								  tc->position.y + (rc->square.dims.y / 2.f));
						break;
					default:
						std::cout << "No such shape found!\n";
						break;
				}
			}
			SwapBuffers();
		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
