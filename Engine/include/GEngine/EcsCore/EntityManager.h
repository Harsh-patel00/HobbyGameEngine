//
// Created by Harsh on 15-01-2022.
//

#include "ComponentManager.h"

namespace ECS
{
#ifndef GAMEENGINE_ENTITYMANAGER_H
#define GAMEENGINE_ENTITYMANAGER_H

   class EntityManager
   {
	   public:
		   // List of all entities created
		   std::vector<Entity> entities;
		   // List of entities that are deleted
		   std::vector<EntityIndex> freeEntities;
		   // Count of entities that not deleted
		   uint AliveEntityCount{};

		   EntityIndex GetEntityIndex(EntityID);

	   public:
		   EntityManager();
		   ~EntityManager();

	   private:
		   void Init();
		   // Entity id contains it's index in the entities array and the entity version
		   // We maintain the version because it helps in identifying that if the entity is deleted and the reused
		   EntityID CreatedEntityId(EntityIndex entityIndex, EntityVersion entityVersion);
		   EntityVersion GetEntityVersion(EntityID);
		   void UpdateAliveEntityCount();

		   // Checks if the component is present/assigned to the entity or not
		   template<typename T>
		   bool IsComponentPresent(EntityID entityId)
		   {
			   return entities[GetEntityIndex(entityId)].mask.test(GetComponentId<T>());
		   }

	   public:
		   // Create a new entity
		   EntityID CreateEntity();
		   // Destroy the created entity
		   void DestroyEntity(EntityID &id);
		   // Set the entity name (Easy to debug)
		   void SetEntityName(EntityID id, const std::string &name);
		   // Get the entity name (Easy to debug)
		   std::string GetEntityName(EntityID id);
		   // To see if the entity is not deleted
		   bool IsEntityValid(EntityID entityId);

		   // Assign the component to the entity
		   template <typename T>
		   void AssignComponent(EntityID id, ComponentManager &cm)
		   {
			   if(!IsEntityValid(id))
			   {
				   std::cout << "Can't assign component : Entity deleted!\n";
				   return;
			   }

			   if(IsComponentPresent<T>(id))
			   {
				   std::cout << "\nCan't assign component : Component already present!\n";
				   return;
			   }

			   cm.AssignComponent<T>(entities[GetEntityIndex(id)]);

			   std::cout << "Component assigned to : " << GetEntityName(id) <<
			   "\nMask : " << entities[GetEntityIndex(id)].mask << "\n";
		   }

		   // Remove assigned component from the entity
		   template<typename T>
		   void RemoveComponent(EntityID id)
		   {
			   if(!IsEntityValid(id))
			   {
				   std::cout << "Can't remove component : Entity deleted!\n";
				   return;
			   }

			   if(!IsComponentPresent<T>(id))
			   {
				   std::cout << "\nCan't remove component : Component not present!\n";
				   return;
			   }

			   entities[GetEntityIndex(id)].mask.reset(GetComponentId<T>());
			   std::cout << typeid(T).name() << " Component removed successfully!\n";
		   }

		   // Try to get the component from the entity
		   // If the component is present, then it returns bool and stores the component in 'val' param
		   // Else it will return false
		   template<typename T>
		   bool TryGetComponent(EntityID id, T &val, ComponentManager &cm)
		   {
			   if(!IsEntityValid(id))
			   {
				   std::cout << "Can't get component : Entity deleted!\n";
				   return false;
			   }

			   if(!IsComponentPresent<T>(id))
			   {
				   std::cout << "Can't get component : Component is not attached to the entity!\n";
				   return false;
			   }

			   val = *(cm.GetComponentFromList<T>(GetEntityIndex(id)));
			   return true;
		   }

		   // Get component from the entity
		   template<typename T>
		   T* GetComponent(EntityID id, ComponentManager &cm)
		   {
			   if(!IsEntityValid(id))
			   {
				   std::cout << "Can't get component : Entity deleted!\n";
				   return nullptr;
			   }

			   if(!IsComponentPresent<T>(id))
			   {
				   std::cout << "Can't get component : Component is not attached to the entity!\n";
				   return nullptr;
			   }

			   return cm.GetComponentFromList<T>(GetEntityIndex(id));
		   }

		   // Set the component value
		   template<typename T>
		   void SetComponentValue(T value, EntityID id, ComponentManager &cm)
		   {
			   if(!IsEntityValid(id))
			   {
				   std::cout << "Can't set component : Entity deleted!\n";
				   return;
			   }

			   if(!IsComponentPresent<T>(id))
			   {
				   std::cout << "Can't set component : Component is not attached to the entity!\n";
				   return;
			   }

			   auto comp = cm.GetComponentFromList<T>(GetEntityIndex(id));

			   *comp = value;
		   }
   };

#endif // GAMEENGINE_ENTITYMANAGER_H
}
