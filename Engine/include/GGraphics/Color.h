//
// Created by Harsh on 13-03-2022.
//

#ifndef GAMEENGINE_COLOR_H
#define GAMEENGINE_COLOR_H

#include <cstdint>
#include <iostream>

namespace GGraphics
{
   enum class ColorEnum : uint32_t
   {
	   // Primary colors
	   RED = 0x00FF0000,        // [0000 0000, 1111 1111, 0000 0000, 0000 0000]
	   GREEN = 0x0000FF00,      // [0000 0000, 0000 0000, 1111 1111, 0000 0000]
	   BLUE = 0x000000FF,       // [0000 0000, 0000 0000, 0000 0000, 1111 1111]

	   YELLOW = RED | GREEN,    // [0000 0000, 1111 1111, 0000 0000, 1111 1111] //  0x00FF00FF
	   MAGENTA = BLUE | RED,     // [0000 0000, 1111 1111, 1111 1111, 0000 0000] // 0x00FFFF00
	   CYAN = GREEN | BLUE,       // [0000 0000, 0000 0000, 1111 1111, 1111 1111] // 0x0000FFFF
	   // Complementary colors

	   WHITE = RED | GREEN | BLUE,
	   BLACK = 0x00000000,

	   GRAY = 0x00333333
   };

   class Color
   {
	   public:
		   uint8_t r{}, g{}, b{};

	   public:
		   Color() = default;
		   Color(uint8_t red, uint8_t green, uint8_t blue) :
			   r(red), g(green), b(blue){}
		   explicit Color(GGraphics::ColorEnum color)
		   {
			   auto packed = static_cast<uint32_t>(color);
			   r = static_cast<uint8_t>((packed >> 16) & 0xFF);
			   g = static_cast<uint8_t>((packed >> 8) & 0xFF);
			   b = static_cast<uint8_t>(packed & 0xFF);
		   }
   };
}
#endif //GAMEENGINE_COLOR_H
