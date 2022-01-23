//
// Created by Harsh on 22-01-2022.
//

#include <memory>
#include "EntityManager.h"

namespace ECS
{
#ifndef GAMEENGINE_ECSMANAGER_H
#define GAMEENGINE_ECSMANAGER_H

   template <typename... ComponentTypes>
   struct EntitiesIterator
   {
	   EntityManager *pScene{nullptr};
	   bool testAllEntities{false};
	   ComponentMask componentMask{};

	   explicit EntitiesIterator(EntityManager &scene) : pScene(&scene)
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

		   Iterator(EntityManager *pScene, EntityIndex index, ComponentMask mask, bool testAllEntities) :
				   pScene(pScene), index(index), componentMask(mask), testAllEntities(testAllEntities) {}

		   EntityID operator*() const
		   {
			   // give back the entityID we're currently at
			   return pScene->entities[index].id;
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
					   pScene->IsEntityValid(pScene->entities[index].id) &&
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
		   while(firstIndex < pScene->entities.size() &&
		         componentMask != (componentMask & pScene->entities[firstIndex].mask) ||
		         !pScene->IsEntityValid(pScene->entities[firstIndex].id))
		   {
			   firstIndex++;
		   }

		   return Iterator(pScene, firstIndex, componentMask, testAllEntities);
	   }

	   Iterator end() const
	   {
		   // Iterator to end of this view
		   return Iterator(pScene, EntityIndex(pScene->entities.size()), componentMask, testAllEntities);
	   }
   };

   class EcsManager
   {
	   private:
		   std::unique_ptr<ECS::EntityManager> entityManager{};
		   std::unique_ptr<ECS::ComponentManager> componentManager{};

	   public:

	   public:
		   EcsManager();
		   ~EcsManager();

	   private:
		   void Init();

	   public:
		   EntityID CreateEntity();
		   void DestroyEntity(EntityID &id);
		   void SetEntityName(EntityID id, const std::string &name);
		   std::string GetEntityName(EntityID id);
		   uint GetAliveEntityCount();

		   template <typename T>
		   void AssignComponent(EntityID id)
		   {
			   entityManager->AssignComponent<T>(id, *componentManager);
		   }

		   template<typename T>
		   void RemoveComponent(EntityID id)
		   {
			   entityManager->RemoveComponent<T>(id);
		   }

		   template<typename T>
		   bool TryGetComponent(EntityID id, T &val)
		   {
			   return entityManager->template TryGetComponent(id, val, *componentManager);
		   }

		   template<typename T>
		   T* GetComponent(EntityID id)
		   {
			   return entityManager->GetComponent<T>(id, *componentManager);
		   }

		   template<typename T>
		   void SetComponentValue(T value, EntityID id)
		   {
			   entityManager->SetComponentValue<T>(value, id, *componentManager);
		   }

		   template<typename... Args>
		   EntitiesIterator<Args...> EntitiesWithComponents()
		   {
			   return EntitiesIterator<Args...>(*entityManager);
		   }
   };


#endif //GAMEENGINE_ECSMANAGER_H
}
