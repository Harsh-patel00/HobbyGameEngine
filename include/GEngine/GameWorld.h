//
// Created by Harsh on 10-01-2022.
//

#include <vector>
#include <memory>
#include "ECS/EntityManager.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEWORLD_H
#define GAMEENGINE_GAMEWORLD_H
	class GameWorld
	{
		private:
			std::unique_ptr<ECS::EntityManager> entityManager;

		public:
			GameWorld();
			~GameWorld();

		public:
			ECS::EntityManager* GetEntityManager();

		private:
			void Init();
	};
#endif //GAMEENGINE_GAMEWORLD_H
}
