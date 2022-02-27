//
// Created by Harsh on 15-01-2022.
//

#include <iostream>
#include <memory>
#include "GEngine/EcsCore/EntityManager.h"

void ECS::EntityManager::Init()
{
   std::cout << "Initializing EntityManager...\n";
}

ECS::EntityID ECS::EntityManager::CreateEntity()
{
	if(!freeEntities.empty())
	{
		EntityIndex newIndex = freeEntities.back();
		freeEntities.pop_back();

		EntityID newID = CreatedEntityId(newIndex,
										 GetEntityVersion(entities[newIndex].eid));
		entities[newIndex].eid = newID;
		UpdateAliveEntityCount();
//		std::cout << "Entity created from free entities!\n";
		return entities[newIndex].eid;
	}

	entities.push_back({CreatedEntityId(entities.size(), 0),
						ComponentMask(),
						"Entity" + std::to_string(entities.size())});
//	std::cout << "New entity created!\n";
	UpdateAliveEntityCount();
	return entities.back().eid;
}

void ECS::EntityManager::DestroyEntity(ECS::EntityID &id)
{
	if (!IsEntityValid(id))
	{
		std::cout << "Trying to destroy already destroyed entity! (Nothing happened)\n";
		return;
	}

	std::cout << GetEntityName(id) << " is destroyed!\n";
	EntityID newID = CreatedEntityId((EntityIndex)-1, GetEntityVersion(id) + 1);
	entities[GetEntityIndex(id)].eid = newID;
	entities[GetEntityIndex(id)].mask.reset();
	freeEntities.push_back(GetEntityIndex(id));
	id = newID;
	UpdateAliveEntityCount();

}

std::string ECS::EntityManager::GetEntityName(ECS::EntityID id)
{
   return entities[GetEntityIndex(id)].name;
}

void ECS::EntityManager::SetEntityName(ECS::EntityID id, const std::string &name)
{
	entities[GetEntityIndex(id)].name = name;
}

ECS::EntityIndex ECS::EntityManager::GetEntityIndex(ECS::EntityID entityId)
{
   return entityId.entId >> 32;
}

ECS::EntityVersion ECS::EntityManager::GetEntityVersion(ECS::EntityID entityId)
{
   return (EntityVersion)entityId.entId;
}

bool ECS::EntityManager::IsEntityValid(ECS::EntityID entityId)
{
   return (entityId.entId >> 32) != (EntityIndex)-1;
}

ECS::EntityID ECS::EntityManager::CreatedEntityId(ECS::EntityIndex entityIndex, ECS::EntityVersion entityVersion)
{
	EntityID entityId{};
	entityId.entId = ((ull)entityIndex << 32) |  ((ull)entityVersion);
	return entityId;
}

void ECS::EntityManager::UpdateAliveEntityCount()
{
	AliveEntityCount = entities.size() - freeEntities.size();
}

ECS::EntityManager::EntityManager()
{
	// std::cout << "EntityManager Constructor\n";
	Init();
}

ECS::EntityManager::~EntityManager()
{
	// std::cout << "EntityManager Destructor\n";
}
