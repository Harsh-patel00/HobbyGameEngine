//
// Created by Harsh on 18-01-2022.
//

#include <vector>
#include "Prerequisite.h"
#include "System.h"

namespace ECS
{
#ifndef GAMEENGINE_SYSTEMMANAGER_H
#define GAMEENGINE_SYSTEMMANAGER_H

   extern int s_systemCounter;

   class SystemManager
   {
	   private:
		   std::vector<System> ActiveSystems{};

	   public:
		   SystemManager();
		   ~SystemManager();

	   public:
		   template<typename T>
		   void RegisterSystem()
		   {
			   int sysId;// = GetSystemId<T>();

			   if(ActiveSystems.size() <= sysId)
			   {
				   ActiveSystems.resize(ActiveSystems.size() + 1);
				   System newSystem(sysId);
				   ActiveSystems.push_back(newSystem);
			   }
			   else
			   {
				   std::cout << "Can't register system twice!\n";
			   }
		   }

		   template<typename T>
		   void StartSystem()
		   {
			   int sysId;// = GetSystemId<T>;
			   for (System sys : ActiveSystems)
			   {
				   if(sys.systemId == sysId)
				   {
					   sys.Run();
					   break;
				   }
			   }
		   }

	   private:
		   void Init();
   };


#endif //GAMEENGINE_SYSTEMMANAGER_H
}
