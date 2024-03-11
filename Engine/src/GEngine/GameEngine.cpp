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

void GEngine::GameEngine::CreateEngineWindow(int windowWidth, int windowHeight, std::string windowTitle)
{
	_windowThread = std::thread([this, &windowWidth, &windowHeight, &windowTitle](){

		std::cout << "\nCreating a window...\n";

		_windowMutex.lock();

		// Limit height to 768 (Max pixels height on the device)
		_window = std::make_unique<EngineWindow>(windowWidth, windowHeight, windowTitle);

		_windowMutex.unlock();
	});

	std::cout << "Creating & running window on thread :: " << _windowThread.get_id() << "\n";

	// Wait for this thread to finish
	_windowThread.join();
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
