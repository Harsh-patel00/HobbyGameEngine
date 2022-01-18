//
// Created by Harsh on 15-01-2022.
//

#include <vector>
#include "Prerequisite.h"

namespace ECS
{
#ifndef GAMEENGINE_COMPONENTMANAGER_H
#define GAMEENGINE_COMPONENTMANAGER_H

   extern int s_componentCounter;
   template <class T>
   int GetComponentId()
   {
	   static int s_componentId = s_componentCounter++;
	   return s_componentId;
   }

   struct ComponentPool
   {
	   char *ComponentData{nullptr};
	   size_t ElementSize{0};

	   explicit ComponentPool(size_t elementSize)
	   {
		   ElementSize = elementSize;
		   ComponentData = new char[elementSize * MAX_ENTITIES]{0};
	   }

	   ~ComponentPool()
	   {
		   delete[] ComponentData;
	   }

	   void* Get(size_t index) const
	   {
		   return ComponentData + (index * ElementSize);
	   }
   };

   class ComponentManager
   {
	   private:
		   // Each index will be a unique component id,
		   // which we will get by GetComponentId()
		   std::vector<ComponentPool*> components{};

	   public:
		   ComponentManager();
		   ~ComponentManager();

	   public:
		   template<typename T>
		   T* GetComponentFromList(EntityIndex entityIndex)
		   {
			    auto componentId = GetComponentId<T>();

			    return static_cast<T*>(components[componentId]->Get(entityIndex));
		   }
		   template<typename T>
		   void AssignComponent(Entity &ent)
		   {
			   int componentId = GetComponentId<T>();

			   if ( components.size() <= componentId )
			   {
				   components.resize(componentId + 1, nullptr);
				   components[componentId] = new ComponentPool(sizeof(T));
				   ent.mask.set(GetComponentId<T>());
			   }
			   else
			   {
				   ent.mask.set(GetComponentId<T>());
			   }
		   }

	   private:
		   void Init();
   };

#endif //GAMEENGINE_COMPONENTMANAGER_H
}