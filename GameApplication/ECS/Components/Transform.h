//
// Created by Harsh on 23-01-2022.
//

#ifndef GAMEENGINE_TRANSFORM_H
#define GAMEENGINE_TRANSFORM_H

#include "GMath/Vector.h"

struct Transform
{
	GMath::Vec3f position{0, 0, 0};
	GMath::Vec3f rotation{0, 0, 0};
	GMath::Vec3f scale{1, 1, 1};

//	GMath::Vec3f localPosition{0, 0, 0};
//	GMath::Vec3f localRotation{0, 0, 0};
//	GMath::Vec3f localScale{1, 1, 1};
};

#endif //GAMEENGINE_TRANSFORM_H
