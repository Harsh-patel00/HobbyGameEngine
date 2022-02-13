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
		   std::vector<Entity> entities;
		   std::vector<EntityIndex> freeEntities;
		   uint AliveEntityCount{};

		   EntityIndex GetEntityIndex(EntityID);

	   public:
		   EntityManager();
		   ~EntityManager();

	   private:
		   void Init();
		   EntityID CreatedEntityId(EntityIndex entityIndex, EntityVersion entityVersion);
		   EntityVersion GetEntityVersion(EntityID);
		   void UpdateAliveEntityCount();

		   template<typename T>
		   bool IsComponentPresent(EntityID entityId)
		   {
			   return entities[GetEntityIndex(entityId)].mask.test(GetComponentId<T>());
		   }

	   public:
		   EntityID CreateEntity();
		   void DestroyEntity(EntityID &id);
		   void SetEntityName(EntityID id, const std::string &name);
		   std::string GetEntityName(EntityID id);
		   bool IsEntityValid(EntityID entityId);

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

//			   std::cout << "\nComponent assigned to : " << GetEntityName(id) <<
//			   "\nMask : " << entities[GetEntityIndex(id)].mask << "\n";
		   }

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
