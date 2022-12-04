//
// Created by Harsh on 10/11/2022.
//

#include <ostream>
#include "Point3.h"

#ifndef GAMEENGINE_POINT4_H
#define GAMEENGINE_POINT4_H

template<typename T>
class Point4
{
	public:
		// A point is 2 dimensional array with only 1 row and 'size' columns
		// This variable is used specially for point and matrix multiplication
		T point[1][4]{};

		T x{}, y{}, z{}, w{};

		// Constructors
		Point4() = default;

		Point4(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;

			point[0][0] = x;
			point[0][1] = y;
			point[0][2] = z;
			point[0][3] = w;
		}

		explicit Point4(const Point3<T> &p3)
		{
			this->x = p3.x;
			this->y = p3.y;
			this->z = p3.z;
			this->w = 1;

			point[0][0] = p3.x;
			point[0][1] = p3.y;
			point[0][2] = p3.z;
			point[0][3] = 1;
		}

	public:
		friend std::ostream &operator<<(std::ostream &os, const Point4 &p)
		{
			os << "Point4 :: { " << p.x << ", " << p.y << ", " << p.z << ", " << p.w << " }";
			return os;
		}

		Point4 operator+(const T &scalar)
		{
			return Point4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
		}

		friend Point4 operator+(const T &scalar, const Point4 &p)
		{
			return Point4(p.x + scalar, p.y + scalar, p.z + scalar, p.w + scalar);
		}

		Point4 operator-(const T &scalar)
		{
			return Point4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
		}

		friend Point4 operator-(const T &scalar, const Point4 &p)
		{
			return Point4(p.x - scalar, p.y - scalar, p.z - scalar, p.w - scalar);
		}

		Point4 operator*(const T &s)
		{
			return Point4(this->x * s, this->y * s, this->z * s, this->w * s);
		}

		friend Point4 operator*(const T &s, const Point4 &p)
		{
			return Point4(p.x * s, p.y * s, p.z * s, p.w * s);
		}
};

#endif //GAMEENGINE_POINT4_H
