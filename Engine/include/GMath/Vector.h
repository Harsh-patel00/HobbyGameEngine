//
// Created by Harsh on 08-01-2022.
//

#include <memory>
#include <cmath>
#include <iostream>
#include "Point.h"

namespace GMath
{
#ifndef GAMEENGINE_MVECTOR_H
#define GAMEENGINE_MVECTOR_H

   template<typename T>
   struct Vector : public Point<T>
   {
	   private:
		   float _length{};
		   // We'll not declare direction variable as vector itself shows the direction

	   public:
		   // Constructors
		   Vector() = default;

		   Vector(T x, T y, T z)
		   {
			   this->x = x;
			   this->y = y;
			   this->z = z;

			   SetLength();
		   }

		   // Member Functions
		   float Dot(const Vector &b)
		   {
			   // a · b = ax * bx + ay * by + az * bz
			   return this->x * b.x + this->y * b.y + this->z * b.z;
		   }

		   Vector Cross(const Vector &b)
		   {
			   // axb = (cx, cy, cz)
			   // cx = aybz − azby
			   // cy = azbx − axbz
			   // cz = axby − aybx

			   return Vector<T>((this->y * b.z - this->z * b.y), (this->z * b.x - this->x * b.z),
			                    (this->x * b.y - this->y * b.x));
		   }

		   float AngleWith(const Vector &b)
		   {
			   // (theta) = cos^-1((a.b)/(|a|*|b|))
			   // 1 degree = 180/PI rads
			   return (acos(this->Dot(b) / (this->_length * b._length)) * 180) / 3.14;
		   }

		   Vector Normalize()
		   {
			   // a(hat) = a / |a|

			   Vector unitVec(this->x / _length, this->y / _length, this->z / _length);

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

	   private:
		   void SetLength()
		   {
			   _length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		   }

	   public:
		   // Overloaded Operators
		   friend std::ostream &operator<<(std::ostream &os, const Vector &v)
		   {
			   os << "Vec(" << v.x << ", " << v.y << ", " << v.z << ")";
			   return os;
		   }

		   friend std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Vector> v)
		   {
			   os << "Vec(" << v->x << ", " << v->y << ", " << v.z << ")";
			   return os;
		   }

		   Vector operator+(const Vector &b)
		   {
			   return Vector(this->x + b.x, this->y + b.y, this->z + b.z);
		   }

		   Vector operator+(const T &s)
		   {
			   return Vector(this->x + s, this->y + s, this->z + s);
		   }

		   Vector operator-()
		   {
			   return Vector(-this->x, -this->y, -this->z);
		   }

		   Vector operator-(const Vector &b)
		   {
			   return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
		   }

		   Vector operator*(const int &s)
		   {
			   return Vector(this->x * s, this->y * s, this->z * s);
		   }

		   friend Vector operator*(const int &s, const Vector &v)
		   {
			   return Vector(v.x * s, v.y * s, v.z * s);
		   }

//		   friend std::ostream& operator<<(std::ostream &os, const Vector &v)
//		   {
//				os << "Vector :: { " << v.x << ", " << v.y << ", " << v.z << " }\n";
//				return os;
//		   }
   };

   using Vec3i = Vector<int>;
   using Vec3f = Vector<float>;
   using Vec3d = Vector<double>;

#endif //GAMEENGINE_MVECTOR_H
}