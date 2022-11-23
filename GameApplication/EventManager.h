//
// Created by Harsh on 12-02-2022.
//

#include "GEngine/Action.h"
#include "GEngine/GWindow/EngineWindow.h"

#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

/*
 * This class stores all Actions that anyone can subscribe to!
 */

class EventManager
{
	public:
		static Action<> QuitGame;

		// Window update will pass a reference to itself
		static Action<void*> WindowUpdate;

	public:
		// Will be notified in input system
		void static NotifyQuitGame()
		{
			QuitGame.Invoke("WindowClosed");
		}

		void static NotifyWindowUpdate(void* windowRef)
		{
			if(!WindowUpdate.IsEmpty())
				WindowUpdate.Invoke(windowRef, "WindowUpdate");
		}
};

//Action<> EventManager::QuitGame{};
//Action<> EventManager::WindowUpdate{};


#endif //GAMEENGINE_EVENTMANAGER_H
