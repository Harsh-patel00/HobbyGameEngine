//
// Created by Harsh on 10/11/2022.
//

#ifndef GAMEENGINE_MPOINT_H
#define GAMEENGINE_MPOINT_H

namespace GMath
{

   template <typename T>
   struct MPoint
   {
	   public:
	        // Member variables
			T x{}, y{}, z{};

	   public:
		   // Constructors
		   MPoint() = default;

#if numPoints == 3
		   MPoint(T x, T y, T z) : x(x), y(y), z(z) {}
#else
		   MPoint(T x, T y) : x(x), y(y){}
#endif
   };

	using Point3i = MPoint<int>;
	using Point3f = MPoint<float>;
	using Point3d = MPoint<double>;
}
#endif //GAMEENGINE_MPOINT_H
