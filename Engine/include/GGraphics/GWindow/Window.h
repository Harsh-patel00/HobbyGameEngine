//
// Created by Harsh on 10-01-2022.
//

#pragma region MACROS

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#pragma endregion

#include <Windows.h>
#include <memory>
#include <iostream>
#include <cassert>

#include "GEngine/Action.h"

namespace GGraphics
{

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

	class Window
	{
		public:
			// Making this static, because I have to use this inside WindowProc function
			static Action<> WindowClosed;

		private:
			// Handle to the created window
			HWND _windowHandle{};

		private:
			// Class name refers to current window class name
			// Window name refers to window title
			const wchar_t *_windowClassName{}, *_windowName{};

		public:
			Window(int windowWidth, int windowHeight, const wchar_t *windowTitle);
			~Window();

		public:
			// This will listen to all user events performed on active window
			void Broadcast();
	};

#endif //GAMEENGINE_WINDOW_H
}