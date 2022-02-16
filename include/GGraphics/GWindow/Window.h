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
			// These are pretty obvious -_-
		int _windowId{};
		int _windowWidth{};
		int _windowHeight{};

	public:
			// Pretty obvious too
		int GetActiveWindowWidth() const;
		int GetActiveWindowHeight() const;
		// Set the active window
		void SetActive() const;

	public:
		Window(int width, int height, const std::string& title);
		~Window();
	};

#endif //GAMEENGINE_WINDOW_H
}