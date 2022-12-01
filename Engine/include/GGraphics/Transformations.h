//
// Created by Harsh on 26/11/2022.
//

#include "GMath/Matrix4x4.h"

#ifndef GAMEENGINE_TRANSFORMATIONS_H
#define GAMEENGINE_TRANSFORMATIONS_H

#define DEG2RAD(x) (x*3.14159f/180)
#define RAD2DEG(x) (x*180/3.14159f)

namespace GGraphics
{
   class Transformation
   {
	   public:

		#pragma region Modelling Transformations

		static GMath::Point3f Translate(GMath::Point3f pointToTranslate, GMath::Point3f position)
		{
		   GMath::Mat4f translationMatrix = GetTranslationMatrix(position);
		   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToTranslate, translationMatrix);
		}

		// rotationAnglePerAxis should contain degrees of rotation in each axis
		static GMath::Point3f Rotate(GMath::Point3f pointToRotate, GMath::Point3f rotationAnglePerAxis)
		{
		   GMath::Mat4f rotationMatrix = GetRotationMatrix(rotationAnglePerAxis);
		   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToRotate, rotationMatrix);
		}

		static GMath::Point3f Scale(GMath::Point3f pointToScale, GMath::Point3f scale)
		{
		   GMath::Mat4f scaleMatrix = GetScaleMatrix(scale);
		   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToScale, scaleMatrix);
		}

		static GMath::Mat4f GetTranslationMatrix(GMath::Point3f position)
		{
		   GMath::Mat4f translationMatrix{};
		   translationMatrix = GMath::Mat4f::GetIdentityMatrix();
		   translationMatrix.mat[0][3] = position.x;
		   translationMatrix.mat[1][3] = position.y;
		   translationMatrix.mat[2][3] = position.z;

		   return translationMatrix;
		}

		// rotationAnglePerAxis has angle in degrees
		static GMath::Mat4f GetRotationMatrix(GMath::Point3f rotationAnglePerAxis)
		{
		   GMath::Mat4f rotationX = GetXRotationMatrix(rotationAnglePerAxis.x);
		   GMath::Mat4f rotationY = GetYRotationMatrix(rotationAnglePerAxis.y);
		   GMath::Mat4f rotationZ = GetZRotationMatrix(rotationAnglePerAxis.z);

		   return rotationZ * rotationY * rotationX;
		}

		// rotationAngleInXAxis in degrees
		static GMath::Mat4f GetXRotationMatrix(float rotationAngleInXAxis)
		{
		   GMath::Mat4f rotationX = GMath::Mat4f::GetIdentityMatrix();
		   rotationX.mat[1][1] = std::cos(DEG2RAD(rotationAngleInXAxis));
		   rotationX.mat[1][2] = std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX.mat[2][1] = -std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX.mat[2][2] = std::cos(DEG2RAD(rotationAngleInXAxis));

		   return rotationX;
		}

		// rotationAngleInYAxis in degrees
		static GMath::Mat4f GetYRotationMatrix(float rotationAngleInYAxis)
		{
		   GMath::Mat4f rotationY = GMath::Mat4f::GetIdentityMatrix();
		   rotationY.mat[0][0] = std::cos(DEG2RAD(rotationAngleInYAxis));
		   rotationY.mat[0][2] = -std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY.mat[2][0] = std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY.mat[2][2] = std::cos(DEG2RAD(rotationAngleInYAxis));

		   return rotationY;
		}

		// rotationAngleInZAxis in degrees
		static GMath::Mat4f GetZRotationMatrix(float rotationAngleInZAxis)
		{
		   GMath::Mat4f rotationZ = GMath::Mat4f::GetIdentityMatrix();
		   rotationZ.mat[0][0] = std::cos(DEG2RAD(rotationAngleInZAxis));
		   rotationZ.mat[0][1] = std::sin(DEG2RAD(rotationAngleInZAxis));
		   rotationZ.mat[1][0] = -std::sin(DEG2RAD(rotationAngleInZAxis));
		   rotationZ.mat[1][1] = std::cos(DEG2RAD(rotationAngleInZAxis));

		   return rotationZ;
		}

		static GMath::Mat4f GetScaleMatrix(GMath::Point3f scale)
		{
		   GMath::Mat4f scaleMatrix{};
		   scaleMatrix = GMath::Mat4f::GetIdentityMatrix();
		   scaleMatrix.mat[0][0] = scale.x;
		   scaleMatrix.mat[1][1] = scale.y;
		   scaleMatrix.mat[2][2] = scale.z;

		   return scaleMatrix;
		}

		#pragma endregion

		#pragma region Viewing Transformations

		static GMath::Mat4f GetWorldToViewMatrix(GMath::Vec3f origin, GMath::Vec3f lookAtPoint, GMath::Vec3f upDirection)
		{
		   // Setup view coordinate system
		   GMath::Vec3f n = (lookAtPoint - origin).Normalize();
		   GMath::Vec3f u = (upDirection.Cross(n)).Normalize();
		   GMath::Vec3f v = n.Cross(u);

		   GMath::Mat4f w2v = GMath::Mat4f::GetIdentityMatrix();

		   w2v.mat[0][0] = u.x;
		   w2v.mat[0][1] = u.y;
		   w2v.mat[0][2] = u.z;
		   w2v.mat[0][3] = -(u.Dot(origin));

		   w2v.mat[1][0] = v.x;
		   w2v.mat[1][1] = v.y;
		   w2v.mat[1][2] = v.z;
		   w2v.mat[1][3] = -(v.Dot(origin));

		   w2v.mat[2][0] = n.x;
		   w2v.mat[2][1] = n.y;
		   w2v.mat[2][2] = n.z;
		   w2v.mat[2][3] = -(n.Dot(origin));

		   return w2v;
		}

		static GMath::Mat4f GetOrthographicProjectionMatrix(float nearPlane, float farPlane, float viewBoxWidth, float viewBoxHeight)
		{
		   GMath::Mat4f projectionMatrix{};

			projectionMatrix = GMath::Mat4f::GetIdentityMatrix();
			projectionMatrix.mat[0][0] = 1/viewBoxWidth;
			projectionMatrix.mat[1][1] = 1/viewBoxHeight;
			projectionMatrix.mat[2][2] = -(2/(nearPlane - farPlane));
			projectionMatrix.mat[2][3] = -((nearPlane + farPlane)/(nearPlane - farPlane));

		   return projectionMatrix;
		}

		static GMath::Mat4f GetPerspectiveProjectionMatrix(float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
		{
		   float fovRadius = 1.f / std::tan(fieldOfView * 0.5f / 180.f * 3.14159f);

		   GMath::Mat4f projectionMatrix{0};
		   projectionMatrix.mat[0][0] = aspectRatio * fovRadius;
		   projectionMatrix.mat[1][1] = fovRadius;
		   projectionMatrix.mat[2][2] = farPlane / (farPlane - nearPlane);
		   projectionMatrix.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
		   projectionMatrix.mat[2][3] = 1;

		   return projectionMatrix;
		}

		#pragma endregion
   };
}

#endif //GAMEENGINE_TRANSFORMATIONS_H
