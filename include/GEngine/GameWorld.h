//
// Created by Harsh on 10-01-2022.
//

#include <vector>
#include "GameObject.h"

namespace GEngine
{
#ifndef GAMEENGINE_GAMEWORLD_H
#define GAMEENGINE_GAMEWORLD_H
	class GameWorld
	{
		/*
		 * GameWorld contains:
		 * 1. All the game objects that are created in this world and Related ops.
		 * 2. Time since the world was created (This will be used for delta time).
		 */


	private:
		std::vector<GameObject*> _allObjectsInGameWorld;


	public:
		void AddToGameWorld(GameObject*);
		bool RemoveFromGameWorld(int id);
		std::vector<GameObject*> GetAllGameWorldObjects();
		GameObject* GetGameObjectInWorld(int id);

	public:
		GameWorld();
		~GameWorld();
	};
#endif //GAMEENGINE_GAMEWORLD_H
}
