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
		static Action<> TestAction2;

	public:
		void static NotifyTestActionPerformed(const std::string& name)
		{
			TestAction.Invoke(name, "TestAction");
		}
};

Action<> EventManager::TestAction{};
Action<> EventManager::TestAction2{};

#endif //GAMEENGINE_EVENTMANAGER_H
