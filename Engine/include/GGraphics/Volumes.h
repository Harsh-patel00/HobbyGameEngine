//
// Created by Harsh on 26/11/2022.
//

#include <cmath>

#ifndef GAMEENGINE_VOLUMES_H
#define GAMEENGINE_VOLUMES_H

namespace GGraphics
{
   // This is a 2D plane on which the projection will be displayed
   struct ViewPort
   {
	   int startX{}, startY{}, width{}, height{};
   };

   // This will be a bounding box for the camera
   struct CanonicalViewVolume
   {
		float width{}, height{}, nearDist{}, farDist{};
   };
}

#endif //GAMEENGINE_VOLUMES_H
