//
// Created by Harsh on 12-03-2022.
//

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

#include <vector>

#include "ECS/Components/Transform.h"

enum class DrawingOrder
{
	Clockwise       = 0,
	Anti_Clockwise  = 1
};

enum class Shape2D
{
	point       = 0,
	line        = 1,
	triangle    = 2,
	rectangle   = 3,
	circle      = 4
};

class Mesh
{
	public:
		// List of points in the mesh
		// [ // This is a list
		//  {1, 2, 3}, // This are the points
		//  {5, 2, 4}
		// ]
		std::vector<GMath::Vec3f> points;

	public:
		void Draw(Shape2D shape, Transform transform);
};


#endif //GAMEENGINE_MESH_H
