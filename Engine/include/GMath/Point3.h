//
// Created by Harsh on 10/11/2022.
//

#include <ostream>

#ifndef GAMEENGINE_POINT3_H
#define GAMEENGINE_POINT3_H

template<typename T>
class Point3
{
	public:
		// A point is 2 dimensional array with only 1 row and 'size' columns
		// This variable is used specially for point and matrix multiplication
		T point[1][3]{};

		T x{}, y{}, z{};

		// Constructors
		Point3() = default;

		Point3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;

			point[0][0] = x;
			point[0][1] = y;
			point[0][2] = z;
		}

	public:
		friend std::ostream &operator<<(std::ostream &os, const Point3 &p)
		{
			os << "Point3 :: { " << p.x << ", " << p.y << ", " << p.z << " }";
			return os;
		}

		Point3 operator+(const T &scalar)
		{
			return Point3(this->x + scalar, this->y + scalar, this->z + scalar);
		}

		friend Point3 operator+(const T &scalar, const Point3 &p)
		{
			return Point3(p.x + scalar, p.y + scalar, p.z + scalar);
		}

		Point3 operator-(const T &scalar)
		{
			return Point3(this->x - scalar, this->y - scalar, this->z - scalar);
		}

		friend Point3 operator-(const T &scalar, const Point3 &p)
		{
			return Point3(p.x - scalar, p.y - scalar, p.z - scalar);
		}

		Point3 operator*(const T &s)
		{
			return Point3(this->x * s, this->y * s, this->z * s);
		}

		friend Point3 operator*(const T &s, const Point3 &p)
		{
			return Point3(p.x * s, p.y * s, p.z * s);
		}

};

#endif //GAMEENGINE_POINT3_H
