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
		/*
		 * GameEngine contains:
		 * 1. Reference to GameWorld
		 * 2. Reference to Coordinator (ECS)
		 */

		private:
			std::unique_ptr<GameWorld> _world;

		public:
			GameEngine();
			~GameEngine();

		public:
			GameWorld* GetGameWorld();

		private:
			void Init();

	};
#endif //GAMEENGINE_GAMEENGINE_H
}
