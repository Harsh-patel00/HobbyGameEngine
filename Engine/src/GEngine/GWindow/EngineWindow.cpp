//
// Created by Harsh on 03/11/2022.
//

#include <iostream>

#include "GEngine/GWindow/EngineWindow.h"

//Action<> GEngine::EngineWindow::WindowClosed{};
//Action<> GEngine::EngineWindow::WindowUpdate{};
Action<> EventManager::QuitGame{};
Action<void*> EventManager::WindowUpdate{};


GEngine::LRESULT GEngine::EngineWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			std::cout << "Window is Destroyed!!\nStop the execution of the program...\n";
			EventManager::NotifyQuitGame();
			_isWindowClosed = true;
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			return 0;

		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			std::cout << "Window resized!\nNew (width, height) : " << "(" << width << ", " << height << ")\n";
			return 0;
		}

		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
}

GEngine::EngineWindow::EngineWindow(int windowWidth, int windowHeight, const wchar_t *windowTitle)
{
	std::cout << "Engine window initializing...\n";

	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	std::cout << "Engine window creation in progress...\n";

	Create(windowTitle, windowWidth, windowHeight);

	std::cout << "Engine window creation done...\n";

	std::cout << "Engine window buffer initialization...\n";

	InitBuffers();

	std::cout << "Engine window buffer initialization done...\n";

	AllocateBitMapInfo();
	_hdc = GEngine::GetDC(Window());

	Show();
}

void GEngine::EngineWindow::Show()
{
	std::cout << "Now showing window....\n";
	GEngine::ShowWindow(Window(), SW_SHOW);

	StartMessageLoop();
}

void GEngine::EngineWindow::StartMessageLoop()
{
	std::cout << "Listening for window messages...\n\n";
	// Run the message loop.
	MSG msg = { };
	while(!_isWindowClosed) // This loop will determine our FPS
	{
		std::cout << "Hiii\n";
		if(GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		OnUpdate();
	}
}

void GEngine::EngineWindow::OnUpdate()
{
	std::cout << "Window Updating...\n";

	SetBkColor(GGraphics::GColor(GGraphics::Color::RED));

	// Every frame should be drawn here!
	EventManager::NotifyWindowUpdate(this);

	SwapBuffers();
}

void GEngine::EngineWindow::InitBuffers()
{
	// Assign memory to both buffers
	AllocateBuffer(_frameBuffer01);
	_frameBuffer02 = nullptr;

	// This will be the default buffer, so use this buffer by default
	_isDefaultBufferActive = true;
}

void GEngine::EngineWindow::AllocateBuffer(void *(&buffer)) const
{
	buffer = VirtualAlloc(
			nullptr,
			// Because we want size of memory as big as screen size
			// as we are storing all pixels (each of size 4 bytes)
			_windowWidth * _windowHeight * sizeof (uint32_t),
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);
}

void GEngine::EngineWindow::DeallocateBuffer(void *(&buffer)) const
{
	GEngine::VirtualFree(
			buffer,
			0,
			MEM_RELEASE);
}

void GEngine::EngineWindow::AllocateBitMapInfo()
{
	_bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
	_bitmapInfo.bmiHeader.biWidth = _windowWidth;
	_bitmapInfo.bmiHeader.biHeight = _windowHeight;
	_bitmapInfo.bmiHeader.biPlanes = 1;
	_bitmapInfo.bmiHeader.biBitCount = 32;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void GEngine::EngineWindow::SetActiveBuffer(void *buffer)
{
	StretchDIBits(_hdc,
	              0, // The x-coordinate of the upper-left corner of the window.
	              0, // The y-coordinate of the upper-left corner of the window.
	              _windowWidth,
	              _windowHeight,
	              0, // The x-coordinate of the source rectangle (framebuffer) in the image.
	              0, // The y-coordinate of the source rectangle (framebuffer) in the image.
	              _windowWidth,      // Framebuffer's width (Same as our window)
	              _windowHeight,    // Framebuffer's height (Same as our window)
	              buffer,              // Array of bytes (Framebuffer) (Color info)
	              &_bitmapInfo,
	              DIB_RGB_COLORS,     // The color table contains literal RGB values.
	              SRCCOPY               // Copies the content from framebuffer to window
	             );
}

void *GEngine::EngineWindow::GetActiveBuffer() const
{
	return (_isDefaultBufferActive) ? _frameBuffer01 : _frameBuffer02;
}

void GEngine::EngineWindow::SwapBuffers()
{
	if(_isDefaultBufferActive)
	{
		_frameBuffer02 = _frameBuffer01;
		_frameBuffer01 = {};
//		AllocateBuffer(_frameBuffer01);
		SetActiveBuffer(_frameBuffer02);
		_isDefaultBufferActive = false;
	}
	else
	{
		_frameBuffer01 = _frameBuffer02;
		_frameBuffer02 = {};
//		AllocateBuffer(_frameBuffer02);
		SetActiveBuffer(_frameBuffer01);
		_isDefaultBufferActive = true;
	}
}

void GEngine::EngineWindow::DrawPixel(int x, int y, GGraphics::GColor newColor)
{
	if(x == _windowWidth)
		x--;

	if(y == _windowHeight)
		y--;

	ColorPixel(x, y, newColor);
}

void GEngine::EngineWindow::DrawPixel(int x, int y)
{
	GGraphics::GColor color(GGraphics::Color::WHITE);
	DrawPixel(x, y, color);
}

void GEngine::EngineWindow::ColorPixel(int x, int y, GGraphics::GColor newColor)
{
	auto *pixel = (uint32_t *)GetActiveBuffer();

	// Convert 3 decimals to hex
	uint32_t color = (newColor.r << 16) ^ (newColor.g << 8) ^ newColor.b;

	pixel += y * _windowWidth + x; // Travel up by y, window width times + move forward by x

	*pixel = color;
}

void GEngine::EngineWindow::SetBkColor(GGraphics::GColor bkColor)
{
	auto *pixel = (uint32_t *)GetActiveBuffer();

	uint32_t color = (bkColor.r << 16) ^ (bkColor.g << 8) ^ bkColor.b;

	for (int i = 0; i < _windowWidth * _windowHeight; ++i)
	{
		*pixel++ = color;
	}
}

GEngine::EngineWindow::~EngineWindow()
{
	DeallocateBuffer(_frameBuffer01);
	DeallocateBuffer(_frameBuffer02);
	ReleaseDC(Window(), _hdc);
}
