//
// Created by Harsh on 13/11/2022.
//

#include "Primitives2d.h"

#ifndef GAMEENGINE_PRIMITIVE3D_H
#define GAMEENGINE_PRIMITIVE3D_H

namespace GGraphics
{
	class Primitives3d
	{
		public:
			// Cube in local coordinates
			struct Cube
			{
				static GGraphics::Primitives2d::Triangle tris[12];
			};
	};

	GGraphics::Primitives2d::Triangle Primitives3d::Cube::tris[12]
	{
			// Front (ABC, ACD)
			{{-0.5f, -0.5f, -0.5f}, {-0.5f, 1, -0.5f}, {1, 1, -0.5f}},
			{{-0.5f, -0.5f, -0.5f}, {1, 1, -0.5f}, {1, -0.5f, -0.5f}},

			// Right (DCF, DFE)
			{{1, -0.5f, -0.5f}, {1, 1, -0.5f}, {1, 1, 1}},
			{{1, -0.5f, -0.5f}, {1, 1, 1}, {1, -0.5f, 1}},

			// Back (EFG, EGH)
			{{1, -0.5f, 1}, {1, 1, 1}, {-0.5f, 1, 1}},
			{{1, -0.5f, 1}, {-0.5f, 1, 1}, {-0.5f, -0.5f, 1}},

			// Left (HGB, HBA)
			{{-0.5f, -0.5f, 1}, {-0.5f, 1, 1}, {-0.5f, 1, -0.5f}},
			{{-0.5f, -0.5f, 1}, {-0.5f, 1, -0.5f}, {-0.5f, -0.5f, -0.5f}},

			// Top (BGF, BFC)
			{{-0.5f, 1, -0.5f}, {-0.5f, 1, 1},  {1, 1, 1}},
			{{-0.5f, 1, -0.5f}, {1, 1, 1}, {1, 1, -0.5f}},

			// Bottom (ADE, AEH)
			{{-0.5f, 1, -0.5f}, {1, -0.5f, -0.5f}, {1, -0.5f, 1}},
			{{-0.5f, 1, -0.5f}, {1, -0.5f, 1}, {-0.5f, -0.5f, 1}},
	};
}

#endif //GAMEENGINE_PRIMITIVE3D_H
