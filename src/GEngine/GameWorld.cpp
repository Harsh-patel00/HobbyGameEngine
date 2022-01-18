//
// Created by Harsh on 10-01-2022.
//

#include <iostream>
#include "GEngine/GameWorld.h"

void GEngine::GameWorld::Init()
{
	std::cout << "Initializing World...\n";
	entityManager = std::make_unique<ECS::EntityManager>();
}

ECS::EntityManager *GEngine::GameWorld::GetEntityManager()
{
	return entityManager.get();
}

GEngine::GameWorld::GameWorld()
{
	// std::cout << "GameWorld Constructor\n";
	Init();
}

GEngine::GameWorld::~GameWorld()
{
	// std::cout << "GameWorld Destructor\n";
	entityManager.reset();
}
