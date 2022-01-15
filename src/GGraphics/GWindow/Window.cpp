//
// Created by Harsh on 10-01-2022.
//

#include "GGraphics/GWindow/Window.h"

GGraphics::Window::Window(int width, int height, char *title)
{
	// Initialization of windows
	_windowId = initwindow(width + 9, height + 13, title, 0, 0, true, true);
	_windowHeight = height;
	_windowWidth = width;
}

GGraphics::Window::~Window()
{
	// Destruction of windows

	closegraph(_windowId);
}

int GGraphics::Window::GetActiveWindowWidth() const
{
	return _windowWidth;
}

int GGraphics::Window::GetActiveWindowHeight() const
{
	return _windowHeight;
}

void GGraphics::Window::SetActive() const
{
	setcurrentwindow(_windowId);
}
