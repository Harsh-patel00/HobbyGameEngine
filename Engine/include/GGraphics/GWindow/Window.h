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
#include "GMath/MVector.h"
#include "GGraphics/GColor.h"

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
			int _windowWidth{}, _windowHeight{};
			HDC _hdc{};

		private:
			// Class name refers to current window class name
			// Window name refers to window title
			const wchar_t *_windowClassName{}, *_windowName{};
			void *_windowMemory{}; // This stores starting address of the memory
			BITMAPINFO _bitmapInfo{};

		public:
			Window(int windowWidth, int windowHeight, const wchar_t *windowTitle);
			~Window();

		public:
			// This will listen to all user events performed on active window
			void Broadcast();
			void PrintWindowDims();

		private:
			// This will put pixel on the screen
			void DrawPixel(int x, int y, GColor color);
			void ColorPixel(int x, int y, GColor color);
			void SetBkColor(GColor color);

			// This assigns a memory of size _windowWidth*_windowHeight and stores in _windowMemory
			void AllocateMemory();
			void AllocateBitMapInfo();
			void OnUpdate();
	};

#endif //GAMEENGINE_WINDOW_H
}