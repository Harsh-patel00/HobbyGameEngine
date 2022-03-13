//
// Created by Harsh on 12-03-2022.
//

#include "GGraphics/Mesh.h"

void Mesh::Draw(Shape2D shape, Transform transform)
{
	switch (shape)
	{
		case Shape2D::point:
			if(points.size() < 1) return;
			break;
		case Shape2D::line:
			if(points.size() < 2) return;
			break;
		case Shape2D::triangle:
			if(points.size() < 3) return;
			break;
		case Shape2D::rectangle:
			if(points.size() < 4) return;
			break;
		case Shape2D::circle:
			if(points.size() < 1) return;
			break;
	}
}
