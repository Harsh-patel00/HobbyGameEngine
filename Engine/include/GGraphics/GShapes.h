//
// Created by Harsh on 13/11/2022.
//

#ifndef GAMEENGINE_GSHAPES_H
#define GAMEENGINE_GSHAPES_H

#include "GMath/MPoint.h"
#include <exception>

namespace GGraphics
{
   enum GShapeType
   {
	   SCircle,
	   SLine
   };

   struct Circle
   {
	   GMath::Point3f center{};
	   float radius{};

	   Circle() = default;
	   Circle(GMath::Point3f centerPoint, float circleRadius) : center(centerPoint), radius(circleRadius) {}
   };

   struct Line
   {
	   GMath::Point3f start{};
	   GMath::Point3f end{};

	   Line() = default;
	   Line(GMath::Point3f startPoint, GMath::Point3f endPoint) : start(startPoint), end(endPoint) {}
   };

	class GShapes
	{
		private:
			GShapeType _currentShape{};
			Circle _circle{};
			Line _line{};

		public:
			GShapeType GetShape();

			void SetLine(GMath::Point3f startPoint, GMath::Point3f endPoint);
			Line GetLine();

			void SetCircle(GMath::Point3f centerPoint, float circleRadius);
			Circle GetCircle();

		private:
			void SetShape(GShapeType shape);

	};
}

#endif //GAMEENGINE_GSHAPES_H
