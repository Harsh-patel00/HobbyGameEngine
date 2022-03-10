//
// Created by Harsh on 15-01-2022.
// This file includes all the typedefs related to ECS and some structs and functions
//

#include <iostream>
#include <bitset>

namespace ECS
{
#ifndef GAMEENGINE_PREREQUISITE_H
#define GAMEENGINE_PREREQUISITE_H

#pragma region Functions

   extern int s_componentCounter;

   template<class T>
   int GetComponentId()
   {
	   static int s_componentId = s_componentCounter++;
	   return s_componentId;
   }
#pragma endregion

#pragma region Typedefs (Built-in Types)

   using ull = unsigned long long;
   using uint = unsigned int;

#pragma endregion

#pragma region Constants

   // Maximum number of unique component allowed
   const uint MAX_COMPONENTS = 5;
   // Maximum number of entities allowed
   const ull MAX_ENTITIES = 10;

#pragma endregion

#pragma region Typedefs (Custom Types)

   // Each entity can have max_components number of components
    using ComponentMask = std::bitset<MAX_COMPONENTS>;

   // Each id is broke into 2 parts
   // 1. EntityIndex   : first 32 bits, index of the list
   // 2. EntityVersion : last 32 bits, version of the entity
    using EntityIndex = uint;
    using EntityVersion = uint;

#pragma endregion

#pragma region Structs

    struct EntityID
   {
	   // Each entity is represented by this
	   ull entId;
   };

    // Actual entity which will be stored in memory
    struct Entity
   {
	   EntityID eid{};
	   ComponentMask mask{};
	   std::string name{};

	   void print() const
	   {
		   std::cout << "Name : " << name << '\n'
		             << "Mask : " << mask << '\n'
		             << "ID : " << eid.entId << '\n';
	   }
   };

#pragma endregion

#endif //GAMEENGINE_PREREQUISITE_H
}
