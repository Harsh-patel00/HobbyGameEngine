//
// Created by Harsh on 01/12/2022.
//

namespace Components
{
#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

   enum class CameraType
   {
	   ORTHOGRAPHIC,
	   PERSPECTIVE
   };

   struct Camera
   {
	   // For view coordinate system
	   GMath::Vec3f  origin{}; // Place of the camera
	   GMath::Vec3f  lookAt{}; // Point to look at from the camera
	   GMath::Vec3f  upDirection{}; // Point to look at from the camera

	   // For projection
	   CameraType type{};

	   float nearPlane{};
	   float farPlane{};
	   float fieldOfView{};
	   float aspectRatio{};
   };

#endif //GAMEENGINE_CAMERA_H
}
