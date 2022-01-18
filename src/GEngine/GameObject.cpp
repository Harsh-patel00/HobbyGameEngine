//
// Created by Harsh on 10-01-2022.
//

#include "GEngine/GameObject.h"
#include "GEngine/GameEngine.h"

int GEngine::GameObject::_gameObjectId = 1;

GEngine::GameObject::GameObject()
{
	std::cout << "Creating GameObject and adding it to GameWorld...\n";
	// GameEngine::GetGameWorld()->AddToGameWorld(this);
	std::cout << "GameObject adding to GameWorld successfully!\n";

	_gameObjectId++;
}

int GEngine::GameObject::GetID()
{
	return _gameObjectId;
}

void GEngine::GameObject::SetAABB(int left, int top, int right, int bottom)
{
	_goAABB = std::make_tuple(left, top, right, bottom);
}

std::tuple<int, int, int, int> GEngine::GameObject::GetAABB() const
{
	return _goAABB;
}
