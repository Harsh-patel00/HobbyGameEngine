//
// Created by Harsh on 10-01-2022.
//

#include "GEngine/GameEngine.h"

GEngine::GameWorld *GEngine::GameEngine::GetGameWorld()
{
	return _world.get();
}

void GEngine::GameEngine::Init()
{
	std::cout << "Initializing Game Engine...\n";
	_world = std::make_unique<GameWorld>();
}

GEngine::GameEngine::GameEngine()
{
	// std::cout << "GameEngine Constructor...\n";
	Init();
}

GEngine::GameEngine::~GameEngine()
{
	// std::cout << "GameEngine Destructor...\n";
	_world.reset();
}
