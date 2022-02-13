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

	private:
		void SwapBuffers()
		{
			// Double Buffering
			setactivepage(getvisualpage());
			setvisualpage(!getactivepage());
			clearviewport();
		}

	public:
		void OnCreate(ECS::EcsManager *em) override
		{
			ECS::System::OnCreate(em);
//			std::cout << "Overridden OnCreate...\n";
		}

		void OnUpdate(float dt, ECS::EcsManager *em) override
		{
			for (auto entId : em->EntitiesWithComponents<Renderer, Transform>())
			{
				auto rc = em->GetComponent<Renderer>(entId);
				auto tc = em->GetComponent<Transform>(entId);

				switch (rc->drawShape)
				{
					case Shape::Circle:
						circle(tc->position.x, tc->position.y, rc->radius);
						break;
//					case Shape::Triangle:
//						// Left
//						line(rc->tris.p1.x, rc->tris.p1.y, rc->tris.p2.x, rc->tris.p2.y);
//						// Right
//						line(rc->tris.p2.x, rc->tris.p2.y, rc->tris.p3.x, rc->tris.p3.y);
//						// Bottom
//						line(rc->tris.p3.x, rc->tris.p3.y, rc->tris.p1.x, rc->tris.p1.y);
//						break;
					case Shape::Square:

//						auto bottom = tc->position.y + (rc->square.dims.y / 2.f);
//						auto top = tc->position.y - (rc->square.dims.y / 2.f);
//						auto left = tc->position.x - (rc->square.dims.x / 2.f);
//						auto right = tc->position.x + (rc->square.dims.x / 2.f);

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
