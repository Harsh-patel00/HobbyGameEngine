//
// Created by Harsh on 01-03-2022.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include "Transform.h"

struct GameObject
{
	Transform transform{};      // Position, Rotation, and Scale
};

#endif //GAMEENGINE_GAMEOBJECT_H
