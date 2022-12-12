//
// Created by Harsh on 12-02-2022.
//

#include "GEngine/EcsCore/System.h"
#include "ECS/Components/InputCon.h"
#include "Utilities/VirtualKeys.h"
#include "Utilities/EngineEventManager.h"

#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

class InputSystem : ECS::System
{
	private:
		GEngine::EngineWindow *pWindow{};

	public:
		explicit InputSystem(const std::string &name) : System(name){}

	private:
		// Function Defs
		void CheckKeys(ECS::EcsManager *em)
		{
			Components::InputControl inputControl{};

			if(pWindow->GetKey(Utilities::KeyCode::W) || pWindow->GetKey(Utilities::KeyCode::ARR_UP))
			{
				inputControl.up = true;
			}

			if(pWindow->GetKey(Utilities::KeyCode::A) || pWindow->GetKey(Utilities::KeyCode::ARR_LEFT))
			{
				inputControl.left = true;
			}

			if(pWindow->GetKey(Utilities::KeyCode::S) || pWindow->GetKey(Utilities::KeyCode::ARR_DOWN))
			{
				inputControl.down = true;
			}

			if(pWindow->GetKey(Utilities::KeyCode::D) || pWindow->GetKey(Utilities::KeyCode::ARR_RIGHT))
			{
				inputControl.right = true;
			}


			for (auto entId : em->EntitiesWithComponents<Components::InputControl>())
			{
				em->SetComponentValue<Components::InputControl>(inputControl, entId);
			}
		}

		void CheckMouse()
		{
//			if(pWindow->GetKey(Utilities::KeyCode::LMOUSEDOWN))
//			{
//				std::cout << "Left mouse Down\n";
//			}
		}

	public:
		void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window) override
		{
			pWindow = window;
//			Events::EngineEventManager::KeyboardHit.AddListener([this](unsigned long long wParam){
//				CheckInput(wParam);
//			});
		}

		void OnUpdate(double dt, GEngine::GameWorld *world) override
		{
			CheckKeys(world->GetEcsManager());
		}
};

#endif //GAMEENGINE_INPUTSYSTEM_H
