//
// Created by Harsh on 23-01-2022.
//

#include "GMath/MVector.h"

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

struct Tris
{
	GMath::Vec3i p1{};
	GMath::Vec3i p2{};
	GMath::Vec3i p3{};
};

struct Square
{
//	float left{};
//	float top{};
//	float right{};
//	float bottom{};

	// Width, Height
	GMath::Vec3i dims{};
};

enum class Shape
{
	Circle,
	//Triangle,
	Square
};

struct Renderer
{
	Shape drawShape{};
	// GMath::Vec3i center{};

	// For circle
	int radius{};

//	// Triangle vertices
//	Tris tris{};

	// For square
	Square square{};
};

#endif //GAMEENGINE_RENDERER_H
