//
// Created by Harsh on 04/12/2022.
//

#ifndef GAMEENGINE_GMATH_H
#define GAMEENGINE_GMATH_H

#include "Point4.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace GMath
{
   using Point3i = Point3<int>;
   using Point3f = Point3<float>;
   using Point3d = Point3<double>;

   using Point4i = Point4<int>;
   using Point4f = Point4<float>;
   using Point4d = Point4<double>;

   using Vec3i = Vector3<int>;
   using Vec3f = Vector3<float>;
   using Vec3d = Vector3<double>;

   using Mat3f = Matrix3x3<float>;
   using Mat3d = Matrix3x3<double>;
   using Mat3i = Matrix3x3<int>;

   using Mat4f = Matrix4x4<float>;
   using Mat4d = Matrix4x4<double>;
   using Mat4i = Matrix4x4<int>;
}
#endif //GAMEENGINE_GMATH_H
