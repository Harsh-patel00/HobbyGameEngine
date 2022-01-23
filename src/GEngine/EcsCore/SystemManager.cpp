//
// Created by Harsh on 18-01-2022.
//

#include "GEngine/EcsCore/SystemManager.h"

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
	std::cout << "Initializing SystemManager...\n";
}
