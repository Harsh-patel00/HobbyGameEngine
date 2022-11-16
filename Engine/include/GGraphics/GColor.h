//
// Created by Harsh on 13-03-2022.
//

#ifndef GAMEENGINE_GCOLOR_H
#define GAMEENGINE_GCOLOR_H

#include <iostream>

namespace GGraphics
{
   enum class GColors
   {
	   // Primary colors
	   RED = 0x00FF0000,        // [0000 0000, 1111 1111, 0000 0000, 0000 0000]
	   GREEN = 0x0000FF00,      // [0000 0000, 0000 0000, 1111 1111, 0000 0000]
	   BLUE = 0x000000FF,       // [0000 0000, 0000 0000, 0000 0000, 1111 1111]
	   // Complimentary colors
	   MAGENTA = 0x00FF00FF,    // [0000 0000, 1111 1111, 0000 0000, 1111 1111]
	   YELLOW = 0x00FFFF00,     // [0000 0000, 1111 1111, 1111 1111, 0000 0000]
	   CYAN = 0x0000FFFF,       // [0000 0000, 0000 0000, 1111 1111, 1111 1111]

	   WHITE = 0x00FFFFFF       // [0000 0000, 1111 1111, 1111 1111, 1111 1111]
   };

   class GColor
   {
	   public:
		   uint32_t r{}, g{}, b{};

	   public:
		   GColor(uint32_t red, uint32_t green, uint32_t blue) :
			   r(red), g(green), b(blue){}
		   explicit GColor(GGraphics::GColors color)
		   {
//			   std::cout << "Color : " << std::hex << (uint32_t)color << "\n";
			   auto x = (uint32_t)color & 0x00FF0000;
//			   std::cout << "Color & 0x00FF0000 : " << std::hex << x << "\n";
				std::flush(std::cout);
			   uint32_t  d = x >> 16;

//			   std::cout << "Color & 0x00FF0000 in int: " << d << "\n";

			   r = (uint32_t)color & 0xFF0000;
			   g = (uint32_t)color & 0x00FF00;
			   b = (uint32_t)color & 0x0000FF;
		   }
   };

}
#endif //GAMEENGINE_GCOLOR_H
