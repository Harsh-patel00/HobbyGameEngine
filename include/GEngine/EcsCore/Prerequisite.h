//
// Created by Harsh on 15-01-2022.
//

#include <iostream>
#include <bitset>

namespace ECS
{
#ifndef GAMEENGINE_PREREQUISITE_H
#define GAMEENGINE_PREREQUISITE_H

   extern int s_componentCounter;

   template<class T>
   int GetComponentId()
   {
	   static int s_componentId = s_componentCounter++;
	   return s_componentId;
   }

   using ull = unsigned long long;
   using uint = unsigned int;

   // Maximum number of unique component allowed
   const uint MAX_COMPONENTS = 5;
   // Maximum number of entities allowed
   const ull MAX_ENTITIES = 10;

   // Each entity is represented by this
   using EntityID = ull;
   // Each EntityID is broke into 2 parts
   // 1. EntityIndex   : first 32 bits, index of the list
   // 2. EntityVersion : last 32 bits, version of the entity
   using EntityIndex = uint;
   using EntityVersion = uint;

   // Each entity can have max_components number of components
   using ComponentMask = std::bitset<MAX_COMPONENTS>;

   struct Entity
   {
	   EntityID id{};
	   ComponentMask mask{};
	   std::string name{};

	   void print() const
	   {
		   std::cout << "Name : " << name << '\n'
		             << "Mask : " << mask << '\n'
		             << "ID : " << id << '\n';
	   }
   };

#endif //GAMEENGINE_PREREQUISITE_H
}
