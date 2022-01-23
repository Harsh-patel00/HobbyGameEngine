//
// Created by Harsh on 10-01-2022.
//

#include "ECS/EcsManager.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEWORLD_H
#define GAMEENGINE_GAMEWORLD_H
	class GameWorld
	{
		private:
			std::unique_ptr<ECS::EcsManager> ecsManager{nullptr};

		public:
			GameWorld();
			~GameWorld();

		public:
			ECS::EcsManager* GetEcsManager();

		private:
			void Init();
	};
#endif //GAMEENGINE_GAMEWORLD_H
}
