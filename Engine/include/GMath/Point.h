//
// Created by Harsh on 10/11/2022.
//

#include <ostream>

#ifndef GAMEENGINE_MPOINT_H
#define GAMEENGINE_MPOINT_H

namespace GMath
{

   template <typename T>
   struct Point
   {
	   public:
	        // Member variables
			T x{}, y{}, z{};

	   public:
		   // Constructors
		   Point() = default;

//#if numPoints == 3
		   Point(T x, T y, T z) : x(x), y(y), z(z) {}
//#else
//		   Point(T x, T y) : x(x), y(y){}
//#endif

		   friend std::ostream& operator<<(std::ostream &os, const Point &p)
		   {
			   os << "Point :: { " << p.x << ", " << p.y << ", " << p.z << " }";
			   return os;
		   }
   };

	using Point3i = Point<int>;
	using Point3f = Point<float>;
	using Point3d = Point<double>;
}
#endif //GAMEENGINE_MPOINT_H
