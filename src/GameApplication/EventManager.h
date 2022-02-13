//
// Created by Harsh on 12-02-2022.
//

#include "GEngine/Action.h"

#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

class EventManager
{
	public:
		static Action<int> RightKeyPressed;
		static Action<int> LeftKeyPressed;

	public:
		void static NotifyRightKeyPressed(int x)
		{
			RightKeyPressed.Invoke(x);
		}

		void static NotifyLeftKeyPressed(int x)
		{
			LeftKeyPressed.Invoke(x);
		}

};

Action<int> EventManager::RightKeyPressed{};
Action<int> EventManager::LeftKeyPressed{};

#endif //GAMEENGINE_EVENTMANAGER_H
