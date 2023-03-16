//
// Created by Harsh on 08-01-2022.
//

#include "Point3.h"

#ifndef GAMEENGINE_VECTOR3_H
#define GAMEENGINE_VECTOR3_H

template<typename T>
struct Vector3 : public Point3<T>
{
	private:
		float _length{};
		// We'll not declare direction variable as vector itself shows the direction

	public:
		// Constructors
		Vector3() = default;

		Vector3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;

			SetLength();
		}

		explicit Vector3(Point3<T> p)
		{
			this->x = p.x;
			this->y = p.y;
			this->z = p.z;

			SetLength();
		}


		// Member Functions
		float Dot(const Vector3 &b)
		{
			// a · b = ax * bx + ay * by + az * bz
			return this->x * b.x + this->y * b.y + this->z * b.z;
		}

		Vector3 Cross(const Vector3 &b)
		{
			// axb = (cx, cy, cz)
			// cx = aybz − azby
			// cy = azbx − axbz
			// cz = axby − aybx

			return Vector3((this->y * b.z - this->z * b.y), (this->z * b.x - this->x * b.z),
			               (this->x * b.y - this->y * b.x));
		}

		float AngleWith(const Vector3 &b)
		{
			// (theta) = cos^-1((a.b)/(|a|*|b|))
			// 1 degree = 180/PI rads
			return (acos(this->Dot(b) / (this->_length * b._length)) * 180) / 3.14;
		}

		Vector3 Normalize()
		{
			// a(hat) = a / |a|

			Vector3 unitVec(this->x / _length, this->y / _length, this->z / _length);

			this->x = unitVec.x;
			this->y = unitVec.y;
			this->z = unitVec.z;
			SetLength();

			return unitVec;
		}

		float GetLength()
		{
			return _length;
		}

		float Distance(const Vector3 &b)
		{
			// Distance from this vector to b
			return Vector3(b - *this).GetLength();
		}

		float Distance(const Point3<T> &p)
		{
			// Distance from this vector to b
			return Vector3(p - *this).GetLength();
		}

	public: // Static functions
		static Vector3 Zero()
		{
			return Vector3(0, 0, 0);
		}

		static Vector3 One()
		{
			return Vector3(1, 1, 1);
		}

		static Vector3 Up()
		{
			return Vector3(0, 1, 0);
		}

		static Vector3 Right()
		{
			return Vector3(1, 0, 0);
		}

		static Vector3 Forward()
		{
			return Vector3(0, 0, 1);
		}

	private:
		void SetLength()
		{
			_length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

	public:
		// Overloaded Operators
		friend std::ostream &operator<<(std::ostream &os, const Vector3 &v)
		{
			os << "Vec(" << v.x << ", " << v.y << ", " << v.z << ")";
			return os;
		}

		Vector3 operator+(const Vector3 &b)
		{
			return Vector3(this->x + b.x, this->y + b.y, this->z + b.z);
		}

		Vector3 operator+(const T &s)
		{
			return Vector3(this->x + s, this->y + s, this->z + s);
		}

		Vector3 &operator-()
		{
			return *(new Vector3(-this->x, -this->y, -this->z));
		}

		Vector3 operator-(const Vector3 &b)
		{
			return Vector3(this->x - b.x, this->y - b.y, this->z - b.z);
		}

		Vector3 operator*(const T &s)
		{
			return Vector3(this->x * s, this->y * s, this->z * s);
		}

		friend Vector3 operator*(const T &s, const Vector3 &v)
		{
			return Vector3(v.x * s, v.y * s, v.z * s);
		}
};

#endif //GAMEENGINE_VECTOR3_H