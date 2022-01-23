//
// Created by Harsh on 20-01-2022.
//

#include <iostream>

namespace ECS
{
#ifndef GAMEENGINE_SYSTEM_H
#define GAMEENGINE_SYSTEM_H

   class System
   {
	   private:
		   float _deltaTime{1/60.f};
	   public:
		   int systemId{};

	   public:
		   explicit System(int);
		   System() = default;
		   ~System();

	   private:
		   void Init();

	   public:
		   void Run();
		   virtual void OnUpdate(float dt);
   };

#endif //GAMEENGINE_SYSTEM_H
}
