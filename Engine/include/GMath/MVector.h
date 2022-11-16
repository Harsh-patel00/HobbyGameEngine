//
// Created by Harsh on 08-01-2022.
//

#include <memory>
#include <cmath>
#include <iostream>
#include "MPoint.h"

namespace GMath
{
#ifndef GAMEENGINE_MVECTOR_H
#define GAMEENGINE_MVECTOR_H

   template<typename T>
   struct MVector : public MPoint<T>
   {
	   private:
		   float _length{};
		   // We'll not declare direction variable as vector itself shows the direction

	   public:
		   // Constructors
		   MVector() = default;

		   MVector(T x, T y, T z)
		   {
			   this->x = x;
			   this->y = y;
			   this->z = z;

			   SetLength();
		   }

		   // Member Functions
		   float Dot(const MVector &b)
		   {
			   // a · b = ax * bx + ay * by + az * bz
			   return this->x * b.x + this->y * b.y + this->z * b.z;
		   }

		   MVector Cross(const MVector &b)
		   {
			   // axb = (cx, cy, cz)
			   // cx = aybz − azby
			   // cy = azbx − axbz
			   // cz = axby − aybx

			   return MVector<T>((this->y * b.z - this->z * b.y), (this->z * b.x - this->x * b.z),
			                     (this->x * b.y - this->y * b.x));
		   }

		   float AngleWith(const MVector &b)
		   {
			   // (theta) = cos^-1((a.b)/(|a|*|b|))
			   // 1 degree = 180/PI rads
			   return (acos(this->Dot(b) / (this->_length * b._length)) * 180) / 3.14;
		   }

		   MVector Normalize()
		   {
			   // a(hat) = a / |a|

			   MVector unitVec(this->x / _length, this->y / _length, this->z / _length);

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
		   friend std::ostream &operator<<(std::ostream &os, const MVector &v)
		   {
			   os << "Vec(" << v.x << ", " << v.y << ", " << v.z << ")";
			   return os;
		   }

		   friend std::ostream &operator<<(std::ostream &os, const std::unique_ptr<MVector> v)
		   {
			   os << "Vec(" << v->x << ", " << v->y << ", " << v.z << ")";
			   return os;
		   }

		   MVector operator+(const MVector &b)
		   {
			   return MVector(this->x + b.x, this->y + b.y, this->z + b.z);
		   }

		   MVector operator+(const T &s)
		   {
			   return MVector(this->x + s, this->y + s, this->z + s);
		   }

		   MVector operator-()
		   {
			   return MVector(-this->x, -this->y, -this->z);
		   }

		   MVector operator-(const MVector &b)
		   {
			   return MVector(this->x - b.x, this->y - b.y, this->z - b.z);
		   }

		   MVector operator*(const int &s)
		   {
			   return MVector(this->x * s, this->y * s, this->z * s);
		   }

		   friend MVector operator*(const int &s, const MVector &v)
		   {
			   return MVector(v.x * s, v.y * s, v.z * s);
		   }
   };

   using Vec3i = MVector<int>;
   using Vec3f = MVector<float>;
   using Vec3d = MVector<double>;

#endif //GAMEENGINE_MVECTOR_H
}