//
// Created by Harsh on 20-01-2022.
//

#include <iostream>
#include "EcsManager.h"

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
		   void Init(const std::string &name);

	   public:
		   virtual void OnUpdate(float dt, EcsManager *ecsManager) = 0;
   };

#endif //GAMEENGINE_SYSTEM_H
}
