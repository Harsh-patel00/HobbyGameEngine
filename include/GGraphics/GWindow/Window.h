//
// Created by Harsh on 10-01-2022.
//

#include <iostream>
#include "graphics.h"

namespace GGraphics
{

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

	class Window
	{
	private:
		int _windowId{};
		int _windowWidth{};
		int _windowHeight{};

	public:
		int GetActiveWindowWidth() const;
		int GetActiveWindowHeight() const;
		void SetActive() const;

	public:
		Window(int width, int height, char *title);
		~Window();
	};

#endif //GAMEENGINE_WINDOW_H
}