//
// Created by Harsh on 22-01-2022.
//

#include <memory>
#include "EntityManager.h"

namespace ECS
{
#ifndef GAMEENGINE_ECSMANAGER_H
#define GAMEENGINE_ECSMANAGER_H

   // Helps to iterate over the entities with specified components
   // If no components are specified, then it will iterate over all entities
   template <typename... ComponentTypes>
   struct EntitiesIterator
   {
	   EntityManager *pEntityManager{nullptr};
	   bool testAllEntities{false};
	   ComponentMask componentMask{};

	   explicit EntitiesIterator(EntityManager &scene) : pEntityManager(&scene)
	   {
		   if (sizeof...(ComponentTypes) == 0)
		   {
			   testAllEntities  = true;
		   }
		   else
		   {
			   // Passed params : Transform, Position, float (Respective IDs : 0, 1, 2)
			   // Index    : 0, 1, 2, 3
			   // Contents : 0, 0, 1, 2 (Because we have used GetID)
			   int componentIds[] = {0, GetComponentId<ComponentTypes>()...};

			   // Run from 1 to last index of above array (i.e. 1, 2, 3)
			   // At which contents are (0, 1, 2)
			   for (int i = 1; i < sizeof...(ComponentTypes) + 1; ++i)
			   {
				   // Set componentMask for components with ids : 0, 1, 2
				   componentMask.set(componentIds[i]);
			   }
		   }
	   }

	   struct Iterator
	   {
		   EntityManager *pScene{nullptr};
		   EntityIndex index{};
		   ComponentMask componentMask{};
		   bool testAllEntities{false};

		   // Iterator implementation because we have to use this in a range-based for loop
		   Iterator(EntityManager *pScene, EntityIndex index, ComponentMask mask, bool testAllEntities) :
				   pScene(pScene), index(index), componentMask(mask), testAllEntities(testAllEntities) {}

		   EntityID operator*() const
		   {
			   // give back the entityID we're currently at
			   return pScene->entities[index].eid;
		   }

		   bool operator==(const Iterator& other) const
		   {
			   // Compare two iterators
			   return index == other.index || index == pScene->entities.size();
		   }

		   bool operator!=(const Iterator& other) const
		   {
			   // Similar to above
			   return index != other.index && index != pScene->entities.size();
		   }

		   bool ValidIndex()
		   {
			   return
				   // It's a valid entity ID
					   pScene->IsEntityValid(pScene->entities[index].eid) &&
					   // It has the correct component mask
					   (testAllEntities || componentMask == (componentMask & pScene->entities[index].mask));
		   }

		   Iterator& operator++()
		   {
			   // Move the iterator forward
			   do
			   {
				   index++;
			   }
			   while(index < pScene->entities.size() && !ValidIndex());
			   return *this;
		   }
	   };

	   Iterator begin() const
	   {
		   // Iterator to beginning of this view
		   EntityIndex firstIndex{0};
		   while(firstIndex < pEntityManager->entities.size() &&
		         componentMask != (componentMask & pEntityManager->entities[firstIndex].mask) ||
		         !pEntityManager->IsEntityValid(pEntityManager->entities[firstIndex].eid))
		   {
			   firstIndex++;
		   }

		   return Iterator(pEntityManager, firstIndex, componentMask, testAllEntities);
	   }

	   Iterator end() const
	   {
		   // Iterator to end of this view
		   return Iterator(pEntityManager, EntityIndex(pEntityManager->entities.size()), componentMask, testAllEntities);
	   }
   };

   class EcsManager
   {
	   private:
		   // Unique entity manager
		   std::unique_ptr<ECS::EntityManager> entityManager{};
		   // Unique component manager
		   std::unique_ptr<ECS::ComponentManager> componentManager{};

	   public:
		   EcsManager();
		   ~EcsManager();

	   private:
		   void Init();

	   public:
		   // Create and register entity
		   EntityID CreateEntity();
		   // Destroy entity
		   void DestroyEntity(EntityID &id);
		   // Set entity name
		   void SetEntityName(EntityID id, const std::string &name);
		   // Get entity name
		   std::string GetEntityName(EntityID id);
		   // Return entities count that are alive
		   uint GetAliveEntityCount();

		   // Assign component to entity
		   template <typename T>
		   void AssignComponent(EntityID id)
		   {
			   std::cout << "Want to attach component type :: " << typeid(T).name() << " to entity(" << id.entId << "):: " << entityManager->GetEntityName(id) << '\n';
			   entityManager->template AssignComponent<T>(id, *componentManager);
		   }

		   // Remove component from entity
		   template<typename T>
		   void RemoveComponent(EntityID id)
		   {
			   entityManager->template RemoveComponent<T>(id);
		   }

		   // Use this when you are not sure if the component assigned to an entity or not!
		   template<typename T>
		   bool TryGetComponent(EntityID id, T &val)
		   {
			   return entityManager->template TryGetComponent<T>(id, val, *componentManager);
		   }

		   // Use this when you are sure that the entity contains specified component
		   // Otherwise use 'TryGetComponent'.
		   template<typename T>
		   T* GetComponent(EntityID id)
		   {
			   return entityManager->template GetComponent<T>(id, *componentManager);
		   }

		   // Set the component value, 1 at a time
		   template<typename T>
		   void SetComponentValue(T value, EntityID id)
		   {
			   entityManager->template SetComponentValue<T>(value, id, *componentManager);
		   }

		   // Iterator for all entities
		   template<typename... Args>
		   EntitiesIterator<Args...> EntitiesWithComponents()
		   {
			   return EntitiesIterator<Args...>(*entityManager);
		   }

		   // Assign and Set component values to default
		   template <typename T>
		   void AssignComponentAndSetDefaultValues(EntityID id)
		   {
			   std::cout << "Setting and assigning component values to ID :: " << id.entId << " Name :: " << entityManager->GetEntityName(id) << '\n';

			   entityManager->template AssignComponent<T>(id, *componentManager);
			   entityManager->template SetComponentValue<T>({}, id, *componentManager);
		   }
   };


#endif //GAMEENGINE_ECSMANAGER_H
}
