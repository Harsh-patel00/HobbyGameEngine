//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include "GMath/MVector.h"

struct Transform
{
	GMath::Vec3f position{};
	GMath::Vec3f rotation{};
	GMath::Vec3f scale{};
};

#endif //GAMEENGINE_TRANSFORM_H
