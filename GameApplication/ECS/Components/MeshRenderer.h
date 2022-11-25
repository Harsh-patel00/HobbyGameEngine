//
// Created by Harsh on 23-01-2022.
//

#include "GGraphics/Primitives2d.h"
#include "GMath/Vector.h"

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

struct MeshRenderer
{
	std::vector<GGraphics::Primitives2d::Triangle> tris{}; // {{0.3, 0.8, 0.4}, {2.2, 3.5, 6.2}, ...}
};

#endif //GAMEENGINE_RENDERER_H
