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
				static Point3f vertices[8];
				static std::vector<int> indices;

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

   //                                                      0, 1, 2, 3, 4, 5, 6, 7
   GMath::Point3f Primitives3d::Cube::vertices[8] {A, B, C, D, E, F, G, H};

   std::vector<int> Primitives3d::Cube::indices
	{
		   // Front (ABC, ACD)
		   0, 1, 2,
		   0, 2, 3,

            // Right (DCF, DFE)
		   3, 2, 5,
		   3, 5, 4,

		   // Back (EFG, EGH)
		   4, 5, 6,
		   4, 6, 7,

		   // Left (HGB, HBA)
		   7, 6, 1,
		   7, 1, 0,

		   // Top (BGF, BFC)
		   1, 6, 5,
		   1, 5, 2,

		   // Bottom (HED, HDA)
			7, 4, 3,
			7, 3, 0
	};
}

#endif //GAMEENGINE_PRIMITIVE3D_H
