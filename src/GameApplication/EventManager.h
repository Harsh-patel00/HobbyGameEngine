//
// Created by Harsh on 12-02-2022.
//

#include "GEngine/Action.h"

#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

/*
 * This class stores all Actions that anyone can subscribe to!
 */

class EventManager
{
	public:
		static Action<> TestAction;

	public:
		void static NotifyTestActionPerformed()
		{
			TestAction.Invoke();
		}
};

Action<> EventManager::TestAction{};

#endif //GAMEENGINE_EVENTMANAGER_H
