//
// Created by Harsh on 15-01-2022.
//

#include <vector>
#include "Prerequisite.h"

namespace ECS
{
#ifndef GAMEENGINE_COMPONENTMANAGER_H
#define GAMEENGINE_COMPONENTMANAGER_H

   // This allocates the memory to store component data in memory
   struct ComponentPool
   {
	   // Actual component data
	   char *ComponentData{nullptr};
	   // Size of Component
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

	   // Get component based on entity index
	   void* Get(size_t index) const
	   {
		   return ComponentData + (index * ElementSize);
	   }
   };

   class ComponentManager
   {
	   private:
		   // List of unique components
		   std::vector<ComponentPool*> components{};

	   public:
		   ComponentManager();
		   ~ComponentManager();

	   private:
		   void Init();

	   public:
		   // Get the component data from components list
		   template<typename T>
		   T* GetComponentFromList(EntityIndex entityIndex)
		   {
			    auto componentId = GetComponentId<T>();

			    return static_cast<T*>(components[componentId]->Get(entityIndex));
		   }

		   // Assign a component to an entity
		   template<typename T>
		   void AssignComponent(Entity &ent)
		   {
			   int componentId = GetComponentId<T>();

			   // If it's a new component, then add it to the list
			   // and set the mask of the entity
			   if ( components.size() <= componentId )
			   {
				   components.resize(componentId + 1, nullptr);
				   components[componentId] = new ComponentPool(sizeof(T));
				   ent.mask.set(GetComponentId<T>());
			   }
			   //Only set the entity mask as the component is already in the list
			   else
			   {
				   ent.mask.set(GetComponentId<T>());
			   }
		   }
   };

#endif //GAMEENGINE_COMPONENTMANAGER_H
}