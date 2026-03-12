//
// Created by Harsh on 15-01-2022.
//

#ifndef GAMEENGINE_COMPONENTMANAGER_H
#define GAMEENGINE_COMPONENTMANAGER_H

#include <vector>
#include <memory>
#include "Prerequisite.h"

namespace ECS
{
   // This allocates the memory to store component data in memory
   struct ComponentPool
   {
	   // Actual component data
	   std::unique_ptr<char[]> ComponentData;
	   // Size of Component
	   size_t ElementSize{0};

	   explicit ComponentPool(size_t elementSize) : ComponentData(std::make_unique<char[]>(elementSize * MAX_ENTITIES)), ElementSize(elementSize)
	   {
	   }

	   ~ComponentPool() = default;

	   // Get component based on entity index
	   void* Get(size_t index) const
	   {
		   return ComponentData.get() + (index * ElementSize);
	   }

	   // Deleted copy operations (non-copyable)
	   ComponentPool(const ComponentPool&) = delete;
	   ComponentPool& operator=(const ComponentPool&) = delete;

	   // Allow move operations
	   ComponentPool(ComponentPool&&) = default;
	   ComponentPool& operator=(ComponentPool&&) = default;
   };

   class ComponentManager
   {
	   private:
		   // List of unique components - using smart pointers instead of raw pointers
		   std::vector<std::unique_ptr<ComponentPool>> components{};

	   public:
		   ComponentManager();
		   ~ComponentManager();

	   private:
		   void Init();

	   public:
		   // Get the component data from components list with bounds checking
		   template<typename T>
		   T* GetComponentFromList(EntityIndex entityIndex)
		   {
				auto componentId = GetComponentId<T>();

				// Add bounds checking to prevent undefined behavior
				if (static_cast<size_t>(componentId) >= components.size() || !components[componentId])
				{
					return nullptr;  // Component not initialized for this entity
				}

				return static_cast<T*>(components[componentId]->Get(entityIndex));
		   }

		   // Assign a component to an entity
		   template<typename T>
		   void AssignComponent(Entity &ent)
		   {
			   int componentId = GetComponentId<T>();

			   // If it's a new component, then add it to the list
			   // and set the mask of the entity
			   if ( static_cast<size_t>(componentId) >= components.size() )
			   {
				   components.resize(componentId + 1);
				   components[componentId] = std::make_unique<ComponentPool>(sizeof(T));

				   // Construct all component instances in the pool using placement new
				   // This is intentional for the ECS pattern - all slots are pre-allocated
				   ComponentPool* pool = components[componentId].get();
				   for (size_t i = 0; i < MAX_ENTITIES; ++i)
				   {
					   new (pool->Get(i)) T();
				   }
			   }

			   // Set the entity mask to indicate this component is assigned
			   ent.mask.set(GetComponentId<T>());
		   }
   };

} // namespace ECS

#endif //GAMEENGINE_COMPONENTMANAGER_H