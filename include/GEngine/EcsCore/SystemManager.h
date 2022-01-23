//
// Created by Harsh on 18-01-2022.
//

#include "System.h"

namespace ECS
{
#ifndef GAMEENGINE_SYSTEMMANAGER_H
#define GAMEENGINE_SYSTEMMANAGER_H

   extern int s_systemCounter;

   template<typename T>
   int GetSystemId()
   {
	   static int s_SystemId = s_systemCounter++;
	   return s_SystemId;
   }


   class SystemManager
   {
	   private:

	   public:
		   SystemManager();
		   ~SystemManager();

	   public:

	   private:
		   void Init();
   };


#endif //GAMEENGINE_SYSTEMMANAGER_H
}
