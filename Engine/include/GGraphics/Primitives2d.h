//
// Created by Harsh on 20-03-2022.
//

#include <cmath>

#include "Color.h"
#include "GEngine/GWindow/EngineWindow.h"
#include "GMath/GMath.h"

#ifndef GAMEENGINE_PRIMITIVES2D_H
#define GAMEENGINE_PRIMITIVES2D_H

using GMath::Point3f;

namespace GGraphics
{
   class Primitives2d
   {
	   public:
		   struct Line
		   {
				   Point3f start{};
				   Point3f end{};

				   Line() = default;

				   Line(Point3f startPoint, Point3f endPoint) : start(startPoint), end(endPoint) {}

				   Line(Point3f startPoint, Point3f endPoint, GEngine::EngineWindow *window, Color lineColor) :
						   start(startPoint), end(endPoint), pDrawWindow(window), color(lineColor) {}

				   void Draw()
				   {
					   // Implement different algorithms in different functions & use them here
					   // TODO: Add Anti-Aliasing algorithm for line
					   UseBresenham();
					   // UseWu();
				   }

				   void Draw(GGraphics::Color lineColor)
				   {
					   color = lineColor;
					   // Implement different algorithms in different functions & use them here
					   // TODO: Add Anti-Aliasing algorithm for line
					   UseBresenham();
					   // UseWu();
				   }

			   private:
				   GEngine::EngineWindow *pDrawWindow{};
				   Color color{GGraphics::ColorEnum::BLACK};

			   private:
				   // This algorithm eliminates all the floating point operations and divisions
				   void UseBresenham()
				   {
					   int  x0 = std::lround(start.x),
					        y0 = std::lround(start.y),
					        x1 = std::lround(end.x),
					        y1 = std::lround(end.y);

					   int dx = std::abs(x1 - x0);
					   int sx = x0 < x1 ? 1 : -1;
					   int dy = -std::abs(y1 - y0);
					   int sy = y0 < y1 ? 1 : -1;
					   int error = dx + dy;

					   while(true)
					   {
						   // If user inputs vertices values outside of the range [-1, 1],
						   // then screen space coordinates will overflow from the memory buffer range.
						   // Ignore those out of range values
						   if(x0 >= 0 && x0 < pDrawWindow->GetWidth() && y0 >= 0 && y0 < pDrawWindow->GetHeight())
						   {
							   pDrawWindow->DrawPixel(x0, y0, color);
						   }

						   if(x0 == x1 && y0 == y1) break;

						   int e2 = 2 * error;

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
			   Point3f points[3] {}; // This array will contain 3 points
			   GMath::Vec3f faceNormal{}; // This is the face normal of the triangle

			   Triangle() = default;
			   Triangle(Point3f p1, Point3f p2, Point3f p3)
			   {
				   points[0] = p1;
				   points[1] = p2;
				   points[2] = p3;

				   CalculateFaceNormals();
			   }

			   void SetDrawColor(GGraphics::Color drawColor)
			   {
				   _triangleDrawColor = drawColor;
			   }

			   void Draw(GEngine::EngineWindow *window, Color lineColor, bool debug = false)
			   {
				   RecalculateNormal();
				   if(debug)
				   {
					   Line{points[0], points[1], window, GGraphics::Color(GGraphics::ColorEnum::RED)}.Draw();
					   Line{points[1], points[2], window, GGraphics::Color(GGraphics::ColorEnum::GREEN)}.Draw();
					   Line{points[2], points[0], window, GGraphics::Color(GGraphics::ColorEnum::BLUE)}.Draw();
				   }
				   else
				   {
					   Line{points[0], points[1], window, lineColor}.Draw();
					   Line{points[1], points[2], window, lineColor}.Draw();
					   Line{points[2], points[0], window, lineColor}.Draw();
				   }
			   }

			   // Set the face normal explicitly
			   void SetFaceNormals(GMath::Vec3f normal)
			   {
				   faceNormal = normal;
			   }

			   // This just recalculates the face normal
			   void RecalculateNormal()
			   {
				   CalculateFaceNormals();
			   }

			   void ShowFaceNormal()
			   {
				   CalculateFaceNormals();

				   GMath::Vec3f avgPos((points[0] + points[1] + points[2]) / 3);

				   Line line1(avgPos.Normalize(), faceNormal);

				   line1.Draw(GGraphics::Color(GGraphics::ColorEnum::GREEN));
			   }

			   void Print()
			   {
				   std::cout << "Point3[0] :: " << points[0] << "\n";
				   std::cout << "Point3[1] :: " << points[1] << "\n";
				   std::cout << "Point3[2] :: " << points[2] << "\n";
			   }

			   bool operator== (GGraphics::Primitives2d::Triangle &tri) const
			   {
				   return points[0] == tri.points[0] && points[1] == tri.points[1] && points[2] == tri.points[2];
			   }

		   private:
			   // Calculate the face normal internally when the triangle is created
			   void CalculateFaceNormals()
			   {
				   Line line1(points[0], points[1]);
				   Line line2(points[2], points[0]);

				   GMath::Vec3f vec1(line1.end - line1.start);
				   GMath::Vec3f vec2(line2.start - line2.end);

				   faceNormal = vec1.Cross(vec2);

				   //std::cout << "Face Normal Raw :: " << faceNormal << '\n';

				   faceNormal.Normalize();

				   //std::cout << "Face Normal Normalized :: " << faceNormal << '\n';

			   }

		   private:
			   GGraphics::Color _triangleDrawColor{GGraphics::Color(GGraphics::ColorEnum::YELLOW)};
		   };
   };
}
#endif //GAMEENGINE_PRIMITIVES2D_H
