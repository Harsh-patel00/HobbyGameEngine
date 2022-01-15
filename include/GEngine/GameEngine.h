//
// Created by Harsh on 10-01-2022.
//

#include "GameWorld.h"
#include "GEngine/ECS/Coordinator.hpp"
#include <memory>

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
		static std::unique_ptr<GameWorld> _world;

	public:
		GameEngine()
		{
			std::cout << "Initializing GameEngine...\n";
		}

		~GameEngine()
		{
			auto deleter = _world.release();
		}

	public:
		static GameWorld *GetGameWorld()
		{
			return _world.get();
		}
	};
#endif //GAMEENGINE_GAMEENGINE_H
}
