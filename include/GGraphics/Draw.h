//
// Created by Harsh on 10-01-2022.
//

#include "GMath/MVector.h"
#include "GEngine/GameObject.h"

namespace GGraphics
{
#ifndef GAMEENGINE_DRAW_H
#define GAMEENGINE_DRAW_H

	class Draw
	{
	public:
		static GEngine::GameObject* Circle(GMath::MVector<int> center, int radius, int color = WHITE);
		static GEngine::GameObject* Line(GMath::MVector<int> start, GMath::MVector<int> end, int color = WHITE);
		static GEngine::GameObject* Box(int left, int top, int right, int bottom, int color = WHITE);
	};


#endif //GAMEENGINE_DRAW_H
}
