//
// Created by Harsh on 26/11/2022.
//

#include "GMath/GMath.h"
#include "Volumes.h"
#include "ECS/Components/Camera.h"

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
		   rotationX[1][2] = -std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX[2][1] = std::sin(DEG2RAD(rotationAngleInXAxis));
		   rotationX[2][2] = std::cos(DEG2RAD(rotationAngleInXAxis));

		   return rotationX;
		}

		// rotationAngleInYAxis in degrees
		static Mat4f GetYRotationMatrix(float rotationAngleInYAxis)
		{
		   Mat4f rotationY = Mat4f::GetIdentityMatrix();
		   rotationY[0][0] = std::cos(DEG2RAD(rotationAngleInYAxis));
		   rotationY[0][2] = std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY[2][0] = -std::sin(DEG2RAD(rotationAngleInYAxis));
		   rotationY[2][2] = std::cos(DEG2RAD(rotationAngleInYAxis));

		   return rotationY;
		}

		// rotationAngleInZAxis in degrees
		static Mat4f GetZRotationMatrix(float rotationAngleInZAxis)
		{
		   Mat4f rotationZ = Mat4f::GetIdentityMatrix();
		   rotationZ[0][0] = std::cos(DEG2RAD(rotationAngleInZAxis));
		   rotationZ[0][1] = -std::sin(DEG2RAD(rotationAngleInZAxis));
		   rotationZ[1][0] = std::sin(DEG2RAD(rotationAngleInZAxis));
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
			Vec3f n = (origin - lookAtPoint).Normalize();
			Vec3f u = (n.Cross(upDirection)).Normalize();
			Vec3f v = u.Cross(n);

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

		static Mat4f GetProjectionMatrix(const Components::Camera &camera)
		{
			float left  = camera.origin.x - (camera.cvv.width / 2);
			float right  = camera.origin.x + (camera.cvv.width / 2);
			float bottom = camera.origin.y - (camera.cvv.height / 2);
			float top    = camera.origin.y + (camera.cvv.height / 2);
			float nearPlane{};
			float farPlane{};
			float size = camera.size;

			if(camera.cvv.nearDist == 0)
			{
				nearPlane = 0.1f;
			}
			else
			{
				nearPlane = camera.cvv.nearDist;
			}

			if( camera.cvv.farDist <= nearPlane)
			{
				farPlane = nearPlane + 0.1f;
			}
			else
			{
				farPlane = camera.cvv.farDist;
			}

			// ------------- PERSPECTIVE PROJECTION SPECIFIC---------------------

			float aspect = camera.cvv.width / camera.cvv.height;
			float fov    = camera.fov; // horizontal fov
			float s = nearPlane * std::tan(DEG2RAD(fov / 2));

			Mat4f projectionMatrix{};
			switch (camera.type)
			{
				case Components::CameraType::ORTHOGRAPHIC:
				{
					projectionMatrix[0][0] = (1 / aspect) / size;

					projectionMatrix[1][1] = 1/size;

					projectionMatrix[2][2] = -2 / (farPlane - nearPlane);
					projectionMatrix[2][3] = -((farPlane + nearPlane) / (farPlane - nearPlane));

					projectionMatrix[3][3] = 1;
					return projectionMatrix;
				}
				case Components::CameraType::PERSPECTIVE:
				{
					top    = camera.origin.y + (s / aspect);
					bottom = camera.origin.y - (s / aspect);
					right  = camera.origin.x + s;
					left  = camera.origin.x - s;

					projectionMatrix[0][0] = 2 * nearPlane / (right - left);

					projectionMatrix[1][1] = 2 * nearPlane / (top - bottom);

					projectionMatrix[2][2] = - (farPlane + nearPlane) / (farPlane - nearPlane);
					projectionMatrix[2][3] = - 2 * farPlane * nearPlane / (farPlane - nearPlane);

					projectionMatrix[3][2] = -1;
					projectionMatrix[3][3] = 0;

					return projectionMatrix;
				}
				default:
					projectionMatrix = -1;
					return projectionMatrix;
			}
		}

		#pragma endregion
   };
}

#endif //GAMEENGINE_TRANSFORMATIONS_H
