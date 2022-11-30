//
// Created by Harsh on 26/11/2022.
//

#include "GMath/Vector.h"
#include "ModellingTransformation.h"

#ifndef GAMEENGINE_VIEWINGTRANSFORMATION_H
#define GAMEENGINE_VIEWINGTRANSFORMATION_H

namespace GGraphics
{
   enum class CameraType
   {
		   ORTHOGRAPHIC,
		   PERSPECTIVE
   };

   class Camera
   {
	   private:
		   GMath::Vec3f u; // x-axis
		   GMath::Vec3f v; // y-axis
		   GMath::Vec3f n; // z-axis
		   GMath::Vec3f origin; // Position of the camera
		   GMath::Vec3f  lookAt; // Point to look at from the camera

	   public:
		   float nearPlane{};
		   float farPlane{};
		   float fov{};
		   float aspectRatio{};
		   float fovRadius{};


	   public:
		   CameraType type{};

	   public:
		   // Default view coordinate system
		   Camera()
		   {
			   origin = GMath::Vec3f(0, 0, -1); // Along the negative z-axis (Towards me)
			   GMath::Vec3f lookAtPoint(0, 0, 0); // We'll always lookAtCenter of the screen
			   GMath::Vec3f upDirection(0, 1, 0); // Y-axis will always be our up direction

			   // Setup view coordinate system
			   n = (origin - lookAtPoint).Normalize();
			   v = (upDirection - origin).Normalize();
			   u = v.Cross(n);
		   }
		   Camera(GMath::Vec3f origin, GMath::Vec3f lookAtPoint, GMath::Vec3f upDirection)
		   {
			   // Setup view coordinate system
			   n = (origin - lookAtPoint).Normalize();
			   v = (upDirection - origin).Normalize();
			   u = v.Cross(n);
		   }
		   Camera(float nearPlane, float farPlane, float fieldOfView, float aspectRatio)
		   {
			   this->nearPlane = nearPlane;
			   this->farPlane = farPlane;
			   fov = fieldOfView;
			   this->aspectRatio = aspectRatio;
			   fovRadius = 1.f / std::tan(fov * 0.5f / 180.f * 3.14159f);
		   }

		   GMath::Point3f WorldToView(GMath::Point3f point)
		   {
			   GMath::Mat4f w2v{};
			   GMath::Mat4f rotationMat = GMath::Mat4f::GetIdentityMatrix();

			   rotationMat.mat[0][0] = u.x;
			   rotationMat.mat[0][1] = u.y;
			   rotationMat.mat[0][2] = u.z;

			   rotationMat.mat[1][0] = v.x;
			   rotationMat.mat[1][1] = v.y;
			   rotationMat.mat[1][2] = v.z;

			   rotationMat.mat[2][0] = n.x;
			   rotationMat.mat[2][1] = n.y;
			   rotationMat.mat[2][2] = n.z;

			   w2v = rotationMat * GGraphics::Transformation::GetTranslationMatrix(-origin);

			   GMath::Point4f intermediatePoint{point, 1};
			   intermediatePoint = w2v * intermediatePoint;

			   GMath::Point3f transformedPoint{
					   intermediatePoint.x / intermediatePoint.w,
					   intermediatePoint.y / intermediatePoint.w,
					   intermediatePoint.z / intermediatePoint.w};

			   return transformedPoint;
		   }

		   GMath::Point3f OrthographicProjection(GMath::Point3f pointToProject, float nearPlaneDistanceFromCameraOrigin)
		   {
			   GMath::Point4f intermediatePoint{pointToProject, 1};

			   GMath::Mat4f transformationMatrix{};
			   transformationMatrix = GMath::Mat4f::GetIdentityMatrix();
			   transformationMatrix.mat[2][2] = 0;
			   transformationMatrix.mat[2][3] = -nearPlaneDistanceFromCameraOrigin;

			   intermediatePoint = transformationMatrix * intermediatePoint;
			   GMath::Point3f translatedPoint{
					   intermediatePoint.x / intermediatePoint.w,
					   intermediatePoint.y / intermediatePoint.w,
					   intermediatePoint.z / intermediatePoint.w};

			   return translatedPoint;
		   }

		   GMath::Point3f PerspectiveProjection(GMath::Point3f pointToProject)
		   {
			   GMath::Point4f intermediatePoint{pointToProject, 1};

			   GMath::Mat4f projectionMatrix{0};
			   projectionMatrix.mat[0][0] = aspectRatio * fovRadius;
			   projectionMatrix.mat[1][1] = fovRadius;
			   projectionMatrix.mat[2][2] = farPlane / (farPlane - nearPlane);
			   projectionMatrix.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			   projectionMatrix.mat[2][3] = 1;

			   intermediatePoint = projectionMatrix * intermediatePoint;

			   GMath::Point3f translatedPoint{};

			   if(intermediatePoint.w != 0)
			   {
				   translatedPoint = {
						   intermediatePoint.x / intermediatePoint.w,
						   intermediatePoint.y / intermediatePoint.w,
						   intermediatePoint.z / intermediatePoint.w};
			   }
			   else
			   {
				   translatedPoint = {
						   intermediatePoint.x,
						   intermediatePoint.y,
						   intermediatePoint.z};
			   }

			   return translatedPoint;
		   }
   };
}

#endif //GAMEENGINE_VIEWINGTRANSFORMATION_H
