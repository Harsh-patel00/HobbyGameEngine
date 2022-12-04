//
// Created by Harsh on 20-01-2022.
//

#include <iostream>
#include "GEngine/GameWorld.h"
#include "GEngine/GWindow/EngineWindow.h"

namespace ECS
{
#ifndef GAMEENGINE_SYSTEM_H
#define GAMEENGINE_SYSTEM_H

   class System
   {
	   public:
		   explicit System(const std::string &);
		   ~System();

	   private:
		   // Prints 'name' is initialized (For debugging)
		   void Init(const std::string &name);

	   public:
		   // NOTE : This function require EcsManager because we may have to go through all entities
		   // so this is the way to get access to entities

		   // This function is called when the system is created
		   virtual void OnCreate(GEngine::GameWorld *world, GEngine::EngineWindow *window) = 0;
		   // This is a pure virtual function, which runs every frame
		   virtual void OnUpdate(double dt, GEngine::GameWorld *world) = 0;
   };

#endif //GAMEENGINE_SYSTEM_H
}
