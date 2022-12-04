//
// Created by Harsh on 13/11/2022.
//

#include "Primitives2d.h"

#ifndef GAMEENGINE_PRIMITIVE3D_H
#define GAMEENGINE_PRIMITIVE3D_H

using GMath::Point3f;

namespace GGraphics
{
	class Primitives3d
	{
		public:
			// Cube in local coordinates (It can be defined anywhere)
			struct Cube
			{
				static GGraphics::Primitives2d::Triangle tris[12];

				private:
					static GMath::Point3f A;
					static GMath::Point3f B;
					static GMath::Point3f C;
					static GMath::Point3f D;
					static GMath::Point3f E;
					static GMath::Point3f F;
					static GMath::Point3f G;
					static GMath::Point3f H;
			};
	};

   GMath::Point3f Primitives3d::Cube::A{-0.5, -0.5, -0.5};
   GMath::Point3f Primitives3d::Cube::B{-0.5, 0.5, -0.5};
   GMath::Point3f Primitives3d::Cube::C{0.5, 0.5, -0.5};
   GMath::Point3f Primitives3d::Cube::D{0.5, -0.5, -0.5};
   GMath::Point3f Primitives3d::Cube::E{0.5, -0.5, 0.5};
   GMath::Point3f Primitives3d::Cube::F{0.5, 0.5, 0.5};
   GMath::Point3f Primitives3d::Cube::G{-0.5, 0.5, 0.5};
   GMath::Point3f Primitives3d::Cube::H{-0.5, -0.5, 0.5};

	GGraphics::Primitives2d::Triangle Primitives3d::Cube::tris[12]
	{
			// Front (ABC, ACD)
			{A, B, C},
			{A, C, D},

			// Right (DCF, DFE)
			{D, C, F},
			{D, F, E},

			// Back (EFG, EGH)
			{E, F, G},
			{E, G, H},

			// Left (HGB, HBA)
			{H, G, B},
			{H, B, A},

			// Top (BGF, BFC)
			{B, G, F},
			{B, F, C},

			// Bottom (HED, HDA)
			{H, E, D},
			{H, D, A},
	};
}

#endif //GAMEENGINE_PRIMITIVE3D_H
