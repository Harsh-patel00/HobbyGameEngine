//
// Created by Harsh on 13-03-2022.
//

#include <iostream>

namespace GGraphics
{

#ifndef GAMEENGINE_GCOLOR_H
#define GAMEENGINE_GCOLOR_H

   enum class GColors
   {
	   // Primary colors
	   RED = 0x00FF0000, // [0000 0000, 1111 1111, 0000 0000, 0000 0000]
	   GREEN = 0x0000FF00, // [0000 0000, 0000 0000, 1111 1111, 0000 0000]
	   BLUE = 0x000000FF, // [0000 0000, 0000 0000, 0000 0000, 1111 1111]
	   // Complimentary colors
	   MAGENTA = 0x00FF00FF, // [0000 0000, 1111 1111, 0000 0000, 1111 1111]
	   YELLOW = 0x00FFFF00, // [0000 0000, 1111 1111, 1111 1111, 0000 0000]
	   CYAN = 0x0000FFFF  // [0000 0000, 0000 0000, 1111 1111, 1111 1111]
   };

   class GColor
   {
	   public:
		   uint32_t r{}, g{}, b{};
   };
}

#endif //GAMEENGINE_GCOLOR_H
