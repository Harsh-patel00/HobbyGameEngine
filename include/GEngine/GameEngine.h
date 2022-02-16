//
// Created by Harsh on 10-01-2022.
//

#include <iostream>
#include <memory>

#include "GameWorld.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEENGINE_H
#define GAMEENGINE_GAMEENGINE_H

	class GameEngine
	{
		private:
			// Maintaining a unique copy of the game world in memory
			// It's a unique pointer because we don't want another world (As of now)
			std::unique_ptr<GameWorld> _world;

		public:
			GameEngine();
			~GameEngine();

		public:
			// Helper function to get reference to GameWorld
			GameWorld* GetGameWorld();

		private:
			void Init();

	};
#endif //GAMEENGINE_GAMEENGINE_H
}
