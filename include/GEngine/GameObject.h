//
// Created by Harsh on 10-01-2022.
//

#include "GGraphics/Shape.h"
#include "GMath/MVector.h"

#include <vector>
#include<tuple>

namespace GEngine
{
#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

	class GameObject
	{
	private:
		static int _gameObjectId;
		std::tuple<int, int, int, int> _goAABB{};

	public:
		GGraphics::Shape shape{};
		GMath::MVector<int> position{0, 0, 0};

	public:
		void SetAABB(int, int, int, int);
		std::tuple<int, int, int, int> GetAABB() const;
		int GetID();

	public:
		GameObject();
	};


#endif //GAMEENGINE_GAMEOBJECT_H
}
