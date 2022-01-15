//
// Created by Harsh on 10-01-2022.
//

#include "GEngine/GameWorld.h"

GEngine::GameWorld::GameWorld()
{
	std::cout << "Initializing GameWorld...\n";
	_allObjectsInGameWorld = {};
}

GEngine::GameWorld::~GameWorld()
{
	std::cout << "Destroying GameWorld...\n";
	_allObjectsInGameWorld.clear();
}

GEngine::GameObject *GEngine::GameWorld::GetGameObjectInWorld(int id)
{
	for (auto go : this->_allObjectsInGameWorld)
	{
		if(go->GetID() == id)
		{
			return go;
		}
	}

	return nullptr;
}

std::vector<GEngine::GameObject *> GEngine::GameWorld::GetAllGameWorldObjects()
{
	return _allObjectsInGameWorld;
}

void GEngine::GameWorld::AddToGameWorld(GEngine::GameObject *gameObject)
{
	_allObjectsInGameWorld.push_back(gameObject);
}

bool GEngine::GameWorld::RemoveFromGameWorld(int id)
{
	for (int i = 0; i < _allObjectsInGameWorld.size(); ++i)
	{
		if (_allObjectsInGameWorld[i]->GetID() == id)
		{
			_allObjectsInGameWorld.erase(_allObjectsInGameWorld.begin() + (i-1));
			return true;
		}
	}
	
	return false;
}

