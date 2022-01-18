//
// Created by Harsh on 15-01-2022.
//

#include <iostream>
#include "GEngine/ECS/EntityManager.h"

void ECS::EntityManager::Init()
{
   std::cout << "Initializing EntityManager...\n";
   componentManager = std::make_unique<ComponentManager>();
}

ECS::EntityID ECS::EntityManager::CreateEntity()
{
	if(!freeEntities.empty())
	{
		EntityIndex newIndex = freeEntities.back();
		freeEntities.pop_back();

		EntityID newID = CreatedEntityId(newIndex,
										 GetEntityVersion(entities[newIndex].id));
		entities[newIndex].id = newID;
		UpdateAliveEntityCount();
		std::cout << "Entity created from free entities!\n";
		return entities[newIndex].id;
	}

	entities.push_back({CreatedEntityId(entities.size(), 0),
						ComponentMask(),
						"Entity" + std::to_string(entities.size())});
	std::cout << "New entity created!\n";
	UpdateAliveEntityCount();
	return entities.back().id;
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
	entities[GetEntityIndex(id)].id = newID;
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
   return entityId >> 32;
}

ECS::EntityVersion ECS::EntityManager::GetEntityVersion(ECS::EntityID entityId)
{
   return (EntityVersion)entityId;
}

bool ECS::EntityManager::IsEntityValid(ECS::EntityID entityId)
{
   return (entityId >> 32) != (EntityIndex)-1;
}

ECS::EntityID ECS::EntityManager::CreatedEntityId(ECS::EntityIndex entityIndex, ECS::EntityVersion entityVersion)
{
	return ((EntityID) entityIndex << 32) |  ((EntityID)entityVersion);
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
