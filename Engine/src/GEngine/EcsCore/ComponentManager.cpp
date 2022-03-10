//
// Created by Harsh on 15-01-2022.
//

#include <iostream>
#include "GEngine/EcsCore/ComponentManager.h"

int ECS::s_componentCounter = 0;

void ECS::ComponentManager::Init()
{
	std::cout << "Initializing ComponentManager...\n";
}

ECS::ComponentManager::ComponentManager()
{
	// std::cout << "ComponentManager Constructor\n";
	Init();
}

ECS::ComponentManager::~ComponentManager()
{
	// std::cout << "ComponentManager Destructor\n";
}

