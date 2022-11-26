//
// Created by Harsh on 10/11/2022.
//

#include <ostream>

#ifndef GAMEENGINE_MPOINT_H
#define GAMEENGINE_MPOINT_H

namespace GMath
{

   template <typename T, int size>
   struct Point
   {
	   public:
		   // A point is 2 dimensional array with only 1 row and 'size' columns
		   // This variable is used specially for point and matrix multiplication
		   T point[1][size]{};

		   T x{}, y{}, z{}, w{};

		   // Constructors
		   Point() = default;
		   Point(T x, T y) : x(x), y(y)
		   {
			   point[0][0] = x;
			   point[0][1] = y;
		   }

		   Point(T x, T y, T z) : x(x), y(y), z(z)
		   {
			   point[0][0] = x;
			   point[0][1] = y;
			   point[0][2] = z;
		   }

		   Point(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
		   {
			   point[0][0] = x;
			   point[0][1] = y;
			   point[0][2] = z;
			   point[0][3] = w;
		   }

		   friend std::ostream& operator<<(std::ostream &os, const Point &p)
		   {
			   if(size == 2)
			        os << "Point :: { " << p.x << ", " << p.y << " }";
			   if(size == 3)
				   os << "Point :: { " << p.x << ", " << p.y << ", " << p.z << " }";
			   if(size == 4)
				   os << "Point :: { " << p.x << ", " << p.y << ", " << p.z << ", " << p.w << " }";
			   return os;
		   }
   };

   using Point2i = Point<int, 2>;
   using Point2f = Point<float, 2>;
   using Point2d = Point<double, 2>;

	using Point3i = Point<int, 3>;
	using Point3f = Point<float, 3>;
	using Point3d = Point<double, 3>;

   using Point4i = Point<int, 4>;
   using Point4f = Point<float, 4>;
   using Point4d = Point<double, 4>;
}
#endif //GAMEENGINE_MPOINT_H
