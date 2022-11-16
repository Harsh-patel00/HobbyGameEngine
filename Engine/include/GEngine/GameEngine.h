//
// Created by Harsh on 10-01-2022.
//

#include <iostream>
#include <memory>
#include <thread>

#include "GameWorld.h"
#include "GWindow/EngineWindow.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEENGINE_H
#define GAMEENGINE_GAMEENGINE_H

	class GameEngine
	{
		private:
			// Run the window on a separate thread, so that inputs does not block the main thread.
			std::thread _windowThread;
			// Maintaining a unique copy of the game world in memory
			// It's a unique pointer because we don't want another world (As of now)
			std::unique_ptr<GameWorld> _world;
			std::unique_ptr<EngineWindow> _window;

		public:
			GameEngine();
			~GameEngine();

		public:
			// Helper function to get reference to GameWorld
			GameWorld* GetGameWorld();
			EngineWindow* GetEngineWindow();

		private:
			void Init();
			void CreateWindowOnSeparateThread();
	};
#endif //GAMEENGINE_GAMEENGINE_H
}
