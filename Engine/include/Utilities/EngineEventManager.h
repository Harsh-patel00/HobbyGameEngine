//
// Created by Harsh on 10/12/2022.
//

#include "Action.h"

namespace Events
{

#ifndef GAMEENGINE_ENGINEEVENTMANAGER_H
#define GAMEENGINE_ENGINEEVENTMANAGER_H

   // This class stores engine and window specific events
   class EngineEventManager
   {
	   public:
		   // Window create will pass a reference to itself
		   static Action<void*> WindowCreate;
		   static Action<double> WindowUpdate;
		   static Action<> WindowResized;
		   static Action<> WindowClosed;
		   static Action<unsigned int> KeyboardHit;

	   public:
		   void static NotifyWindowClose()
		   {
			   if(!WindowClosed.IsEmpty())
				   WindowClosed.Invoke("WindowClosed");
		   }

		   void static NotifyWindowResize()
		   {
			   if(!WindowResized.IsEmpty())
				   WindowResized.Invoke("WindowResized");
		   }

		   void static NotifyWindowUpdate(double elapsedTime)
		   {
			   if(!WindowUpdate.IsEmpty())
				   WindowUpdate.Invoke(elapsedTime, "WindowUpdate");
		   }

		   void static NotifyWindowCreate(void* windowRef)
		   {
			   if(!WindowCreate.IsEmpty())
				   WindowCreate.Invoke(windowRef, "WindowCreate");
		   }

		   void static NotifyKeyboardHit(unsigned int uMsg)
		   {
			   if(!KeyboardHit.IsEmpty())
				   KeyboardHit.Invoke(uMsg, "KeyboardHit");
		   }
   };


#endif //GAMEENGINE_ENGINEEVENTMANAGER_H
}
