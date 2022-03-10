//
// Created by Harsh on 12-02-2022.
//

#include "GEngine/EcsCore/System.h"

#include "ECS/Components/InputCon.h"

#include "EventManager.h"


#ifndef GAMEENGINE_INPUTSYSTEM_H
#define GAMEENGINE_INPUTSYSTEM_H

class InputSystem : ECS::System
{
	public:
		explicit InputSystem(const std::string &name) : System(name){}

	private:
		// Function Defs
		/*
		void CheckMouse()
		{
			int mousePosX = 0;
			int mousePosY = 0;

			// On mouse move
			if(ismouseclick(WM_MOUSEMOVE))
			{
				getmouseclick(WM_MOUSEMOVE, mousePosX, mousePosY);
				clearmouseclick(WM_MOUSEMOVE);
			}

#pragma region LeftButton

			if(ismouseclick(WM_LBUTTONDOWN))
			{
				getmouseclick(WM_LBUTTONDOWN, mousePosX, mousePosY);

				showerrorbox("Mouse Clicked!");

				clearmouseclick(WM_LBUTTONDOWN);
			}
			if(ismouseclick(WM_LBUTTONUP))
			{
				getmouseclick(WM_LBUTTONUP, mousePosX, mousePosY);
				clearmouseclick(WM_LBUTTONUP);
			}
			if(ismouseclick(WM_LBUTTONDBLCLK))
			{
				getmouseclick(WM_LBUTTONDBLCLK, mousePosX, mousePosY);
				clearmouseclick(WM_LBUTTONDBLCLK);
			}

#pragma endregion

#pragma region RightButton

			if(ismouseclick(WM_RBUTTONDOWN))
			{
				getmouseclick(WM_RBUTTONDOWN, mousePosX, mousePosY);
				clearmouseclick(WM_RBUTTONDOWN);

				EventManager::NotifyTestActionPerformed("RbuttonDown");
				EventManager::TestAction2.Invoke("RbuttonDown", "TestAction2");

			}
			if(ismouseclick(WM_RBUTTONUP))
			{
				getmouseclick(WM_RBUTTONUP, mousePosX, mousePosY);
				clearmouseclick(WM_RBUTTONUP);
			}
			if(ismouseclick(WM_RBUTTONDBLCLK))
			{
				getmouseclick(WM_RBUTTONDBLCLK, mousePosX, mousePosY);
				clearmouseclick(WM_RBUTTONDBLCLK);
			}

#pragma endregion

#pragma region MiddleButton

			if(ismouseclick(WM_MBUTTONDOWN))
			{
				getmouseclick(WM_MBUTTONDOWN, mousePosX, mousePosY);
				clearmouseclick(WM_MBUTTONDOWN);
			}
			if(ismouseclick(WM_MBUTTONUP))
			{
				getmouseclick(WM_MBUTTONUP, mousePosX, mousePosY);
				clearmouseclick(WM_MBUTTONUP);
			}
			if(ismouseclick(WM_MBUTTONDBLCLK))
			{
				getmouseclick(WM_MBUTTONDBLCLK, mousePosX, mousePosY);
				clearmouseclick(WM_MBUTTONDBLCLK);
			}

#pragma endregion
		}

		void CheckKeys(ECS::EcsManager *em)
		{
			if (kbhit() == true)
			{
				if ( GetAsyncKeyState(VK_ESCAPE) || char(toupper(getch())) == 'Q' )
				{
					std::cout << "Exiting...\n";

					exit(EXIT_SUCCESS);
				}

				if (GetAsyncKeyState(VK_RIGHT))
				{
					for (auto ent : em->EntitiesWithComponents<InputControl>())
					{
						auto ic = em->GetComponent<InputControl>(ent);
						em->SetComponentValue<InputControl>({ic->right = true, false, false, false}, ent);
					}

//					EventManager::NotifyRightKeyPressed(4);
				}

				if (GetAsyncKeyState(VK_LEFT))
				{
					for (auto ent : em->EntitiesWithComponents<InputControl>())
					{
						auto ic = em->GetComponent<InputControl>(ent);
						em->SetComponentValue<InputControl>({false, ic->left = true, false, false}, ent);
					}

//					EventManager::NotifyLeftKeyPressed(8);
				}

				if(char(toupper(getch())) == 'G')
				{
					std::cout << "Adding myfunc as listener...\n";
					EventManager::TestAction2.AddListener(MyFunc2);
				}
			}
		}
		*/
	public:
		void OnCreate(GEngine::GameWorld *world) override
		{
			ECS::System::OnCreate(world);
//			std::cout << "Overridden OnCreate...\n";
		}

		void OnUpdate(float dt, GEngine::GameWorld *world) override
		{
			// CheckKeys(world->GetEcsManager());
			// CheckMouse();
		}
};

#endif //GAMEENGINE_INPUTSYSTEM_H
