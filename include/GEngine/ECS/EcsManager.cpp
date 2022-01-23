//
// Created by Harsh on 22-01-2022.
//

#include "EcsManager.h"

ECS::EcsManager::EcsManager()
{
	// std::cout << "EcsManager Constructor\n";
	Init();
}

ECS::EcsManager::~EcsManager()
{
	// std::cout << "GameWorld Destructor\n";
}

void ECS::EcsManager::Init()
{
	std::cout << "Initializing EcsManager...\n";
	entityManager = std::make_unique<ECS::EntityManager>();
	componentManager = std::make_unique<ECS::ComponentManager>();
	systemManager = std::make_unique<ECS::SystemManager>();
}

ECS::EntityID ECS::EcsManager::CreateEntity()
{
	return entityManager->CreateEntity();
}

void ECS::EcsManager::DestroyEntity(ECS::EntityID &id)
{
	entityManager->DestroyEntity(id);
}

void ECS::EcsManager::SetEntityName(ECS::EntityID id, const std::string &name)
{
	entityManager->SetEntityName(id, name);
}

std::string ECS::EcsManager::GetEntityName(ECS::EntityID id)
{
	return entityManager->GetEntityName(id);
}

ECS::uint ECS::EcsManager::GetAliveEntityCount()
{
	return entityManager->AliveEntityCount;
}
