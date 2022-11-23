//
// Created by Harsh on 18/11/2022.
//
#include "GGraphics/GShapes.h"

GGraphics::GShapeType GGraphics::GShapes::GetShape()
{
	return _currentShape;
}

void GGraphics::GShapes::SetLine(GMath::Point3f startPoint, GMath::Point3f endPoint)
{
	_line = {startPoint, endPoint};
	SetShape(SLine);
}

GGraphics::Line GGraphics::GShapes::GetLine()
{
	return _line;
}

void GGraphics::GShapes::SetCircle(GMath::Point3f centerPoint, float circleRadius)
{
	_circle = {centerPoint, circleRadius};
	SetShape(SCircle);
}

GGraphics::Circle GGraphics::GShapes::GetCircle()
{
	return _circle;
}

void GGraphics::GShapes::SetShape(GShapeType shapeType)
{
	_currentShape = shapeType;
}

