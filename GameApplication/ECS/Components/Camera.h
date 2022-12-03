//
// Created by Harsh on 01/12/2022.
//

#include "GGraphics/Volumes.h"

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

	   GGraphics::CanonicalViewVolume cvv{};
	   GGraphics::ViewPort viewport{};
   };

#endif //GAMEENGINE_CAMERA_H
}
