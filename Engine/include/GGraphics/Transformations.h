//
// Created by Harsh on 26/11/2022.
//

#include "GMath/GMath.h"
#include "Volumes.h"

#ifndef GAMEENGINE_TRANSFORMATIONS_H
#define GAMEENGINE_TRANSFORMATIONS_H

#define DEG2RAD(x) (x*3.14159f/180)
#define RAD2DEG(x) (x*180/3.14159f)

using namespace GMath;

namespace GGraphics
{
   class Transformation
   {
	   public:

		#pragma region Modelling Transformations

		static Point3f Translate(const Point3f& pointToTranslate, const Point3f& position)
		{
		   Mat4f translationMatrix = GetTranslationMatrix(position);
		   return translationMatrix * pointToTranslate;
		}

		// rotationAnglePerAxis should contain degrees of rotation in each axis
		static Point3f Rotate(const Point3f& pointToRotate, const Point3f& rotationAnglePerAxis)
		{
		   Mat4f rotationMatrix = GetRotationMatrix(rotationAnglePerAxis);
		   return rotationMatrix * pointToRotate;
		}

		static Point3f Scale(Point3f pointToScale, Point3f scale)
		{
		   Mat4f scaleMatrix = GetScaleMatrix(scale);
		   return scaleMatrix * pointToScale;
		}

		static Mat4f GetTranslationMatrix(const Point3f& position)
		{
		   Mat4f translationMatrix{};
		   translationMatrix = Mat4f::GetIdentityMatrix();
		   translationMatrix[0][3] = position.x;
		   translationMatrix[1][3] = position.y;
		   translationMatrix[2][3] = position.z;

		   return translationMatrix;
		}

		// rotationAnglePerAxis has angle in degrees
		static Mat4f GetRotationMatrix(const Point3f& rotationAnglePerAxis)
		{
		   Mat4f rotationX = GetXRotationMatrix(rotationAnglePerAxis.x);
		   Mat4f rotationY = GetYRotationMatrix(rotationAnglePerAxis.y);
		   Mat4f rotationZ = GetZRotationMatrix(rotationAnglePerAxis.z);

		   // Order of rotation (Right to Left)
		   // 1. Rotate in Z
		   // 2. Rotate in Y
		   // 3. Rotate in X
		   return rotationX * rotationY * rotationZ;
		}

		// rotationAngleInXAxis in degrees
		static Mat4f GetXRotationMatrix(float rotationAngleInXAxis)
		{
		   Mat4f rotationX = Mat4f::GetIdentityMatrix();
		   rotationX[1][1] = std::cos(DEG2RAD(rotationAngleInXAxis));
		   rotationX[1][2] = std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX[2][1] = -std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX[2][2] = std::cos(DEG2RAD(rotationAngleInXAxis));

		   return rotationX;
		}

		// rotationAngleInYAxis in degrees
		static Mat4f GetYRotationMatrix(float rotationAngleInYAxis)
		{
		   Mat4f rotationY = Mat4f::GetIdentityMatrix();
		   rotationY[0][0] = std::cos(DEG2RAD(rotationAngleInYAxis));
		   rotationY[0][2] = -std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY[2][0] = std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY[2][2] = std::cos(DEG2RAD(rotationAngleInYAxis));

		   return rotationY;
		}

		// rotationAngleInZAxis in degrees
		static Mat4f GetZRotationMatrix(float rotationAngleInZAxis)
		{
		   Mat4f rotationZ = Mat4f::GetIdentityMatrix();
		   rotationZ[0][0] = std::cos(DEG2RAD(rotationAngleInZAxis));
		   rotationZ[0][1] = std::sin(DEG2RAD(rotationAngleInZAxis));
		   rotationZ[1][0] = -std::sin(DEG2RAD(rotationAngleInZAxis));
		   rotationZ[1][1] = std::cos(DEG2RAD(rotationAngleInZAxis));

		   return rotationZ;
		}

		static Mat4f GetScaleMatrix(const Point3f& scale)
		{
		   Mat4f scaleMatrix{};
		   scaleMatrix = Mat4f::GetIdentityMatrix();
		   scaleMatrix[0][0] = scale.x;
		   scaleMatrix[1][1] = scale.y;
		   scaleMatrix[2][2] = scale.z;

		   return scaleMatrix;
		}

		#pragma endregion

		#pragma region Viewing Transformations

		static Mat4f GetWorldToViewMatrix(Vec3f origin, Vec3f lookAtPoint, Vec3f upDirection)
		{
			// Setup view coordinate system
			Vec3f n = (lookAtPoint - origin).Normalize();
			Vec3f u = (upDirection.Cross(n)).Normalize();
			Vec3f v = n.Cross(u);

			Mat4f w2v = Mat4f::GetIdentityMatrix();

			w2v[0][0] = u.x;
			w2v[0][1] = u.y;
			w2v[0][2] = u.z;
			w2v[0][3] = -(u.Dot(origin));

			w2v[1][0] = v.x;
			w2v[1][1] = v.y;
			w2v[1][2] = v.z;
			w2v[1][3] = -(v.Dot(origin));

			w2v[2][0] = n.x;
			w2v[2][1] = n.y;
			w2v[2][2] = n.z;
			w2v[2][3] = -(n.Dot(origin));

			return w2v;
		}

		static Mat4f GetOrthographicProjectionMatrix(GGraphics::CanonicalViewVolume cvv)
		   {
				if(cvv.nearDist >= cvv.farDist || cvv.farDist <= cvv.nearDist)
					cvv.farDist = cvv.nearDist + 0.01f;

			   Mat4f projectionMatrix{};

			   projectionMatrix = Mat4f::GetIdentityMatrix();
				projectionMatrix[0][0] = 2 / cvv.width;
				projectionMatrix[1][1] = 2 / cvv.height;
				projectionMatrix[2][2] = 2 / (cvv.farDist - cvv.nearDist);
				projectionMatrix[2][3] = (cvv.farDist + cvv.nearDist) / (cvv.farDist - cvv.nearDist);

			   return projectionMatrix;
		   }

		static Mat4f GetPerspectiveProjectionMatrix(GGraphics::CanonicalViewVolume cvv)
		{
		   Mat4f projectionMatrix{0};
		   projectionMatrix[0][0] = (2 * cvv.nearDist) / cvv.width;
		   projectionMatrix[1][1] = (2 * cvv.nearDist) / cvv.height;
		   projectionMatrix[2][2] = ((cvv.nearDist + cvv.farDist) / (cvv.nearDist - cvv.farDist));
		   projectionMatrix[2][3] = ((2 * cvv.nearDist * cvv.farDist) / (cvv.nearDist - cvv.farDist));
		   projectionMatrix[3][2] = 1;

		   return projectionMatrix;
		}

		#pragma endregion
   };
}

#endif //GAMEENGINE_TRANSFORMATIONS_H
