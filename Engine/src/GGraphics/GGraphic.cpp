//
// Created by Harsh on 20-03-2022.
//

#include "GGraphics/GGraphic.h"
#include "GMath/MVector.h"

void GGraphics::GGraphic::SetBrushColor(GColor brushColor)
{
	_brushColor = brushColor;
}

void GGraphics::GGraphic::Draw(GGraphics::GShapes shapeClass, GEngine::EngineWindow *window)
{
	pDrawWindow = window;
	this->shapeClass = shapeClass;

	switch (shapeClass.GetShape())
	{
		case SCircle:
			DrawCircle();
			break;
		case SLine:
			DrawLine();
			break;
		default:
			std::cout << "No such shape found!\n";
	}
}


void GGraphics::GGraphic::DrawCircle()
{

}

void GGraphics::GGraphic::DrawLine()
{
//	GMath::Vec3i start{20, 20, 0};
//	GMath::Vec3i end{60, 60, 0};
	auto line = shapeClass.GetLine();
	float i = 0.;

	while(i < 1.)
	{
		int x = line.start.x + (line.end.x-line.start.x) * i;
		int y = line.start.y + (line.end.y-line.start.y) * i;

		pDrawWindow->DrawPixel(x, y, _brushColor);

		i+=0.01;
	}
}
