//
// Created by Harsh on 20-03-2022.
//

#include <cmath>

#include "Color.h"
#include "GEngine/GWindow/EngineWindow.h"
#include "GMath/Point.h"

#ifndef GAMEENGINE_PRIMITIVES2D_H
#define GAMEENGINE_PRIMITIVES2D_H

namespace GGraphics
{
   class Primitives2d
   {
	   public:
		   struct Line
		   {
				   GMath::Point3f start{};
				   GMath::Point3f end{};

				   Line() = default;

				   Line(GMath::Point3f startPoint, GMath::Point3f endPoint, GEngine::EngineWindow *window, Color lineColor) :
						   start(startPoint), end(endPoint), pDrawWindow(window), color(lineColor) {}

				   void Draw()
				   {
					   // Implement different algorithms in different functions & use them here
					   // TODO: Add Anti-Aliasing algorithm for line
					   UseBresenham();
					   // UseWu();
				   }

			   private:
				   GEngine::EngineWindow *pDrawWindow{};
				   Color color{};

			   private:
				   void UseBresenham()
				   {
					   float x0 = start.x, y0 = start.y, x1 = end.x, y1 = end.y;

					   float dx = std::abs(x1 - x0);
					   int sx = x0 < x1 ? 1 : -1;
					   float dy = -std::abs(y1 - y0);
					   int sy = y0 < y1 ? 1 : -1;
					   float error = dx + dy;

					   while(true)
					   {
						   pDrawWindow->DrawPixel(x0, y0, color);
						   if(x0 == x1 && y0 == y1) break;
						   float e2 = 2 * error;
						   if(e2 >= dy)
						   {
							   if(x0 == x1) break;
							   error = error + dy;
							   x0 = x0 + sx;
						   }
						   if(e2 <= dx)
						   {
							   if(y0 == y1) break;
							   error = error + dx;
							   y0 = y0 + sy;
						   }
					   }
				   }

#pragma region // Wu's algorithm
				   void plot(int x, int y, float c)
				   {
					   // Set brightness of the color

					   color = GGraphics::Color(ColorEnum::RED);

					   color.r *= c;
					   color.g *= c;
					   color.b *= c;

					   pDrawWindow->DrawPixel(x, y, color);
				   }

				   // integer part of x
				   auto ipart(auto x)
				   {
					   return std::floor(x);
				   }

				   auto round(auto x)
				   {
					   return ipart(x + 0.5f);
				   }

				   // fractional part of x
				   auto fpart(auto x)
				   {
					   return x - floor(x);
				   }

				   auto rfpart(auto x)
				   {
					   return 1 - fpart(x);
				   }

				   void swap(auto &a, auto &b)
				   {
					   float temp = a;
					   a = b;
					   b = temp;
				   }

				   void UseWu()
				   {
					   auto x0 = start.x, y0 = start.y, x1 = end.x, y1 = end.y;

					   auto steep = std::abs(y1 - y0) > std::abs(x1 - x0);

					   if(steep)
					   {
						   swap(x0, y0);
						   swap(x1, y1);
					   }

					   if(x0 > x1)
					   {
						   swap(x0, x1);
						   swap(y0, y1);
					   }

					   auto dx = x1 - x0;
					   auto dy = y1 - y0;
					   auto gradient = dx == 0.f ? 1.f : (dy / dx);

					   // handle first endpoint
					   auto xend = round(x0);
					   auto yend = y0 + gradient * (xend - x0);
					   auto xgap = rfpart(x0 + 0.5);
					   auto xpxl1 = xend; // this will be used in the main loop
					   auto ypxl1 = ipart(yend);

					   if(steep)
					   {
						   plot(ypxl1, xpxl1, rfpart(yend) * xgap);
						   plot(ypxl1 + 1, xpxl1, fpart(yend) * xgap);
					   }
					   else
					   {
						   plot(xpxl1, ypxl1, rfpart(yend) * xgap);
						   plot(xpxl1, ypxl1 + 1, fpart(yend) * xgap);
					   }

					   auto intery = yend + gradient; // first y-intersection for the main loop

					   // handle second endpoint
					   xend = round(x1);
					   yend = y1 + gradient * (xend - x1);
					   xgap = fpart(x1 + 0.5);
					   auto xpxl2 = xend; //this will be used in the main loop
					   auto ypxl2 = ipart(yend);

					   if(steep)
					   {
						   plot(ypxl2, xpxl2, rfpart(yend) * xgap);
						   plot(ypxl2 + 1, xpxl2, fpart(yend) * xgap);
					   }
					   else
					   {
						   plot(xpxl2, ypxl2, rfpart(yend) * xgap);
						   plot(xpxl2, ypxl2 + 1, fpart(yend) * xgap);
					   }

					   // main loop
					   if(steep)
					   {
						   for (auto x = xpxl1 + 1; x == xpxl2 - 1; x++)
						   {
							   plot(ipart(intery), x, rfpart(intery));
							   plot(ipart(intery) + 1, x, fpart(intery));
							   intery = intery + gradient;
						   }
					   }
					   else
					   {
						   for (auto x = xpxl1 + 1; x == xpxl2 - 1; x++)
						   {
							   plot(x, ipart(intery), rfpart(intery));
							   plot(x, ipart(intery) + 1, fpart(intery));
							   intery = intery + gradient;
						   }
					   }
				   }

#pragma endregion
		   };
		   struct Triangle
		   {
			   GMath::Point3f points[3] {}; // This array will contain 3 points

			   Triangle() = default;
			   Triangle(GMath::Point3f p1, GMath::Point3f p2, GMath::Point3f p3)
			   {
				   points[0] = p1;
				   points[1] = p2;
				   points[2] = p3;
			   }

			   void Draw(GEngine::EngineWindow *window, Color lineColor)
			   {
				   Line{points[0], points[1], window, lineColor}.Draw();
				   Line{points[1], points[2], window, lineColor}.Draw();
				   Line{points[2], points[0], window, lineColor}.Draw();
			   }
		   };
   };
}
#endif //GAMEENGINE_PRIMITIVES2D_H
