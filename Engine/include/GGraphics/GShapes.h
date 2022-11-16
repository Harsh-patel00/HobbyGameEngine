//
// Created by Harsh on 13/11/2022.
//

#ifndef GAMEENGINE_GSHAPES_H
#define GAMEENGINE_GSHAPES_H

#include "GMath/MPoint.h"

class GShapes
{
	struct Circle
	{
		GMath::Point3f center{};
		float radius{};
	};

	struct Line
	{
		GMath::Point3f start{};
		GMath::Point3f end{};
	};
};


#endif //GAMEENGINE_GSHAPES_H
