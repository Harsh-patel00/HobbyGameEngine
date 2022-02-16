//
// Created by Harsh on 10-01-2022.
//

#include "EcsCore/EcsManager.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEWORLD_H
#define GAMEENGINE_GAMEWORLD_H
	class GameWorld
	{
		private:
			// Maintains a unique copy of EcsManager in memory
			// It's an unique pointer because we don't want another copy of EcsManager in memory
			std::unique_ptr<ECS::EcsManager> ecsManager{nullptr};

		public:
			GameWorld();
			~GameWorld();

		public:
			// Helper function to get the reference to EcsManager
			ECS::EcsManager* GetEcsManager();

		private:
			void Init();
	};
#endif //GAMEENGINE_GAMEWORLD_H
}
