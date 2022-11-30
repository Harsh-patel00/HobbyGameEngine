//
// Created by Harsh on 26/11/2022.
//

#include "GMath/Matrix4x4.h"

#ifndef GAMEENGINE_MODELLINGTRANSFORMATION_H
#define GAMEENGINE_MODELLINGTRANSFORMATION_H

#define DEG2RAD(x) (x*3.14159f/180)
#define RAD2DEG(x) (x*180/3.14159f)

namespace GGraphics
{
   class Transformation
   {
	   public:
		   GMath::Point3f static Translate(GMath::Point3f pointToTranslate, GMath::Point3f position)
		   {
			   GMath::Mat4f translationMatrix = GetTranslationMatrix(position);
			   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToTranslate, translationMatrix);
		   }

		   // rotationAnglePerAxis should contain degrees of rotation in each axis
		   GMath::Point3f static Rotate(GMath::Point3f pointToRotate, GMath::Point3f rotationAnglePerAxis)
		   {
			   GMath::Mat4f rotationMatrix = GetRotationMatrix(rotationAnglePerAxis);
			   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToRotate, rotationMatrix);
		   }

		   GMath::Point3f static Scale(GMath::Point3f pointToScale, GMath::Point3f scale)
		   {
			   GMath::Mat4f scaleMatrix = GetScaleMatrix(scale);
			   return GMath::Mat4f::Matrix4Vec3Multiplication(pointToScale, scaleMatrix);
		   }

		   GMath::Mat4f static GetTranslationMatrix(GMath::Point3f position)
		   {
			   GMath::Mat4f translationMatrix{};
			   translationMatrix = GMath::Mat4f::GetIdentityMatrix();
			   translationMatrix.mat[0][3] = position.x;
			   translationMatrix.mat[1][3] = position.y;
			   translationMatrix.mat[2][3] = position.z;

			   return translationMatrix;
		   }

		   // rotationAnglePerAxis has angle in degrees
		   GMath::Mat4f static GetRotationMatrix(GMath::Point3f rotationAnglePerAxis)
		   {
			   GMath::Mat4f rotationX = GetXRotationMatrix(rotationAnglePerAxis.x);
			   GMath::Mat4f rotationY = GetYRotationMatrix(rotationAnglePerAxis.y);
			   GMath::Mat4f rotationZ = GetZRotationMatrix(rotationAnglePerAxis.z);

			   return rotationZ * rotationY * rotationX;
		   }

		   // rotationAngleInXAxis in degrees
		   GMath::Mat4f static GetXRotationMatrix(float rotationAngleInXAxis)
		   {
			   GMath::Mat4f rotationX = GMath::Mat4f::GetIdentityMatrix();
			   rotationX.mat[1][1] = std::cos(DEG2RAD(rotationAngleInXAxis));
			   rotationX.mat[1][2] = std::sin(DEG2RAD(rotationAngleInXAxis));
			   rotationX.mat[2][1] = -std::sin(DEG2RAD(rotationAngleInXAxis));
			   rotationX.mat[2][2] = std::cos(DEG2RAD(rotationAngleInXAxis));

			   return rotationX;
		   }

		   // rotationAngleInYAxis in degrees
		   GMath::Mat4f static GetYRotationMatrix(float rotationAngleInYAxis)
		   {
			   GMath::Mat4f rotationY = GMath::Mat4f::GetIdentityMatrix();
			   rotationY.mat[0][0] = std::cos(DEG2RAD(rotationAngleInYAxis));
			   rotationY.mat[0][2] = -std::sin(DEG2RAD(rotationAngleInYAxis));
			   rotationY.mat[2][0] = std::sin(DEG2RAD(rotationAngleInYAxis));
			   rotationY.mat[2][2] = std::cos(DEG2RAD(rotationAngleInYAxis));

			   return rotationY;
		   }

		   // rotationAngleInZAxis in degrees
		   GMath::Mat4f static GetZRotationMatrix(float rotationAngleInZAxis)
		   {
			   GMath::Mat4f rotationZ = GMath::Mat4f::GetIdentityMatrix();
			   rotationZ.mat[0][0] = std::cos(DEG2RAD(rotationAngleInZAxis));
			   rotationZ.mat[0][1] = std::sin(DEG2RAD(rotationAngleInZAxis));
			   rotationZ.mat[1][0] = -std::sin(DEG2RAD(rotationAngleInZAxis));
			   rotationZ.mat[1][1] = std::cos(DEG2RAD(rotationAngleInZAxis));

			   return rotationZ;
		   }

		   GMath::Mat4f static GetScaleMatrix(GMath::Point3f scale)
		   {
			   GMath::Mat4f scaleMatrix{};
			   scaleMatrix = GMath::Mat4f::GetIdentityMatrix();
			   scaleMatrix.mat[0][0] = scale.x;
			   scaleMatrix.mat[1][1] = scale.y;
			   scaleMatrix.mat[2][2] = scale.z;

			   return scaleMatrix;
		   }
   };
}

#endif //GAMEENGINE_MODELLINGTRANSFORMATION_H
