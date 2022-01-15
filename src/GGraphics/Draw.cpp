//
// Created by Harsh on 10-01-2022.
//

#include "graphics.h"
#include "GGraphics/Draw.h"
#include "GEngine/GameObject.h"
#include "GEngine/GameWorld.h"

GEngine::GameObject* GGraphics::Draw::Circle(GMath::MVector<int> center, int radius, int color)
{
	// Draw circle
	setcolor(color);
	circle(center.x, center.y, radius);

	// Create a new game object
	auto *circleGO = new GEngine::GameObject();

	// Set new game object attributes
	circleGO->position = center;
	circleGO->shape = Shape::CIRCLE;

	// Calculate AABB
	int left, right, top, bottom;

	left = center.x - radius;
	right = center.x + radius;
	top = center.y + radius;
	bottom = center.y - radius;

	circleGO->SetAABB(left, top, right, bottom);

	return circleGO;
}

GEngine::GameObject* GGraphics::Draw::Line(GMath::MVector<int> start, GMath::MVector<int> end, int color)
{
	setcolor(color);
	line(start.x, start.y, end.x, end.y);

	return nullptr;
}

GEngine::GameObject* GGraphics::Draw::Box(int left, int top, int right, int bottom, int color)
{
	setcolor(color);
	rectangle(left, top, right, bottom);

	return nullptr;
}
