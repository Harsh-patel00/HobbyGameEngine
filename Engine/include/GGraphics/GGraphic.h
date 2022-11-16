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
		   GColor _brushColor;

	   public:
		   void SetBrushColor(GColor brushColor)
		   {
				_brushColor = brushColor;
		   }
		   void Draw(GShapes shape, const GEngine::EngineWindow& window)
		   {

		   }
   };

}
#endif //GAMEENGINE_GGRAPHICS_H
