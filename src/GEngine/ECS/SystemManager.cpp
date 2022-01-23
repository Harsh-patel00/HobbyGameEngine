//
// Created by Harsh on 18-01-2022.
//

#include "GEngine/ECS/SystemManager.h"

int ECS::s_systemCounter = 0;

ECS::SystemManager::SystemManager()
{
	Init();
}

ECS::SystemManager::~SystemManager()
{

}

void ECS::SystemManager::Init()
{
	std::cout << "Initializing system manager...\n";
}
