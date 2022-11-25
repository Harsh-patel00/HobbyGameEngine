//
// Created by Harsh on 13-03-2022.
//

#ifndef GAMEENGINE_COLOR_H
#define GAMEENGINE_COLOR_H

#include <iostream>

namespace GGraphics
{
   enum class ColorEnum
   {
	   // Primary colors
	   RED = 0x00FF0000,        // [0000 0000, 1111 1111, 0000 0000, 0000 0000]
	   GREEN = 0x0000FF00,      // [0000 0000, 0000 0000, 1111 1111, 0000 0000]
	   BLUE = 0x000000FF,       // [0000 0000, 0000 0000, 0000 0000, 1111 1111]

	   // Complimentary colors
	   YELLOW = RED | GREEN,    // [0000 0000, 1111 1111, 0000 0000, 1111 1111] //  0x00FF00FF
	   MAGENTA = BLUE | RED,     // [0000 0000, 1111 1111, 1111 1111, 0000 0000] // 0x00FFFF00
	   CYAN = GREEN | BLUE,       // [0000 0000, 0000 0000, 1111 1111, 1111 1111] // 0x0000FFFF

	   WHITE = RED | GREEN | BLUE,     // [0000 0000, 1111 1111, 1111 1111, 1111 1111] // 0x00FFFFFF
	   BLACK = RED & GREEN & BLUE
   };

   class Color
   {
	   public:
		   uint32_t r{}, g{}, b{};

	   public:
		   Color() = default;
		   Color(uint32_t red, uint32_t green, uint32_t blue) :
			   r(red), g(green), b(blue){}
		   explicit Color(GGraphics::ColorEnum color)
		   {
			   r = ((uint32_t)color & 0x00FF0000) >> 16;
			   g = ((uint32_t)color & 0x0000FF00) >> 8;
			   b = (uint32_t)color & 0x000000FF;
		   }
   };
}
#endif //GAMEENGINE_COLOR_H
