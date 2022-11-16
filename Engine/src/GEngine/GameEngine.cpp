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
	std::cout << "Initializing Game Engine...Thread ID :: " << std::this_thread::get_id() << "\n";
	_world = std::make_unique<GameWorld>();

	CreateWindowOnSeparateThread();
}

void GEngine::GameEngine::CreateWindowOnSeparateThread()
{
	_windowThread = std::thread([this](){
		std::cout << "\nCreating a window...\n";
		_window = std::make_unique<EngineWindow>(500, 600, L"Gagged Engine");
	});

	std::cout << "Window running on thread :: " << _windowThread.get_id() << "\n";

	_windowThread.detach();
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

GEngine::EngineWindow *GEngine::GameEngine::GetEngineWindow()
{
	return _window.get();
}
