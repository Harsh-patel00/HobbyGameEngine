//
// Created by Harsh on 10-01-2022.
//

#include <iostream>
#include "GEngine/GameWorld.h"

void GEngine::GameWorld::Init()
{
	std::cout << "Initializing World...\n";
	ecsManager = std::make_unique<ECS::EcsManager>();
}

ECS::EcsManager *GEngine::GameWorld::GetEcsManager()
{
	return ecsManager.get();
}

GEngine::GameWorld::GameWorld()
{
	// std::cout << "GameWorld Constructor\n";
	Init();
}

GEngine::GameWorld::~GameWorld()
{
	// std::cout << "GameWorld Destructor\n";
	ecsManager.reset();
}

