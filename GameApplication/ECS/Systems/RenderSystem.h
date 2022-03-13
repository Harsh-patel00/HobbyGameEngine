//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_RENDERSYSTEM_H
#define GAMEENGINE_RENDERSYSTEM_H

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/GameObject.h"
#include "GMath/MVector.h"
#include "EventManager.h"

#include "GGraphics/GWindow/Window.h"

class RenderSystem : ECS::System
{
	private:
		 std::unique_ptr<GGraphics::Window> window;
	public:
		explicit RenderSystem(const std::string &name) : System(name){}

	private:
		void StartWindow()
		{
			// Create a unique window here
			// This makes sense, as we create a render system, we should have something to render on
			window = std::make_unique<GGraphics::Window>(800, 600, L"Game Engine");

			// This will listen to the WindowClosed action from the window class.
			// I have created this to notify the game, that window is closed,
			// because window is not in user's control.
			GGraphics::Window::WindowClosed.AddListener(EventManager::NotifyQuitGame);

			window->PrintWindowDims();

		}

	public:
		void OnCreate(GEngine::GameWorld *world) override
		{
			// Calling base OnCreate (As of now it does nothing)
			ECS::System::OnCreate(world);
			// std::cout << "Overridden OnCreate...\n";

			StartWindow();
		}
		void OnUpdate(float dt, GEngine::GameWorld *world) override
		{
			// TODO : Check whether this is the proper place to create and show the window

			// This function will listen to any user action performed on window
			window->Broadcast();

			// Looping through all entities with Transform and Render component
			for (auto entId : world->GetEcsManager()->EntitiesWithComponents<GameObject>())
			{
				auto go = world->GetEcsManager()->GetComponent<GameObject>(entId);

				// TODO : Implement draw function
				// go->renderer->mesh.Draw(tc->position, tc->rotation, tc->scale);
			}

		}
};

#endif //GAMEENGINE_RENDERSYSTEM_H
