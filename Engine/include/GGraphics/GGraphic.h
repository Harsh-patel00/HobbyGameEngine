//
// Created by Harsh on 20-03-2022.
//

#ifndef GAMEENGINE_GGRAPHICS_H
#define GAMEENGINE_GGRAPHICS_H

#include "GColor.h"
#include "GShapes.h"
#include "GEngine/GWindow/EngineWindow.h"

namespace GGraphics
{
   class GGraphic
   {
	   private:
		   GColor _brushColor{};
		   GEngine::EngineWindow *pDrawWindow;
		   GGraphics::GShapes shapeClass;

	   public:
		   void SetBrushColor(GColor brushColor);
		   void Draw(GGraphics::GShapes shapeClass, GEngine::EngineWindow *window);

	   private:
			void DrawCircle();
			void DrawLine();
   };

}
#endif //GAMEENGINE_GGRAPHICS_H
