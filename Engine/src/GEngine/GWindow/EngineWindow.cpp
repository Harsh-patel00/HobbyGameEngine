//
// Created by Harsh on 03/11/2022.
//

#include <iostream>
#include "GEngine/GWindow/EngineWindow.h"

Action<void*> Events::EngineEventManager::WindowCreate{};
Action<double> Events::EngineEventManager::WindowUpdate{};
Action<unsigned int> Events::EngineEventManager::KeyboardHit{};
Action<> Events::EngineEventManager::WindowResized{};
Action<> Events::EngineEventManager::WindowClosed{};

bool isKeyPressed = false;
bool isKeyHold = false;
bool isKeyUp = false;

GEngine::LRESULT GEngine::EngineWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			std::cout << "Window is Destroyed!!\nStop the execution of the program...\n";
			Events::EngineEventManager::NotifyWindowClose();
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

			HandleWindowResize(width, height);

			return 0;
		}

		case WM_KEYDOWN:
			if(!isKeyHold)
			{
				isKeyPressed = true;
			}
			return 0;

		case WM_KEYUP:
			isKeyUp = true;
			isKeyPressed = false;
			isKeyHold = false;
			return 0;

		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
}

GEngine::EngineWindow::EngineWindow(int windowWidth, int windowHeight, std::string windowTitle)
{
	std::cout << "Engine window initializing...\n";

	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_windowTitle = windowTitle;

	std::cout << "Engine window creation in progress...\n";

	// Convert from string to wstring
	std::wstring widestr = std::wstring(windowTitle.begin(), windowTitle.end());

	Create(widestr.c_str(), windowWidth, windowHeight, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	std::cout << "Engine window creation done...\n";

	std::cout << "Engine window buffer initialization...\n";

	InitBuffers();

	std::cout << "Engine window buffer initialization done...\n";

	AllocateBitMapInfo();
	_hdc = GEngine::GetDC(Window());

	Events::EngineEventManager::NotifyWindowCreate(this);

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
		if(GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		OnUpdate();

		std::string finalWindowTitle = _windowTitle + " :: FPS :: " + std::to_string(1/_elapsedTime.count());
		std::wstring finalWindowTitleW = std::wstring(finalWindowTitle.begin(), finalWindowTitle.end());
		GEngine::SetWindowTextW(Window(), finalWindowTitleW.c_str());
	}
}

void GEngine::EngineWindow::OnUpdate()
{
	auto start = std::chrono::high_resolution_clock::now();
	ClearBg();

	// Every frame should be drawn here!
	Events::EngineEventManager::NotifyWindowUpdate(_elapsedTime.count());

	SwapBuffers();
	auto end = std::chrono::high_resolution_clock::now();
	_elapsedTime = end - start;
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
	              buffer,              // Array of bytes (Framebuffer) (ColorEnum info)
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

void GEngine::EngineWindow::DrawPixel(int x, int y, GGraphics::Color newColor)
{
	if(x == _windowWidth)
		x--;

	if(y == _windowHeight)
		y--;

	ColorPixel(x, y, newColor);
}

void GEngine::EngineWindow::ColorPixel(int x, int y, GGraphics::Color newColor)
{
	auto *pixel = (uint32_t *)GetActiveBuffer();

	// Convert 3 decimals to hex
	uint32_t color = (newColor.r << 16) ^ (newColor.g << 8) ^ newColor.b;

	pixel += y * _windowWidth + x; // Travel up by y, window width times + move forward by x

	*pixel = color;
}

void GEngine::EngineWindow::ClearBg(GGraphics::Color bkColor)
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

int GEngine::EngineWindow::GetWidth()
{
	return _windowWidth;
}

int GEngine::EngineWindow::GetHeight()
{
	return _windowHeight;
}

void GEngine::EngineWindow::HandleWindowResize(int newWidth, int newHeight)
{
	DeallocateBuffer(_frameBuffer01);
	DeallocateBuffer(_frameBuffer02);

	_windowWidth = newWidth;
	_windowHeight = newHeight;

	AllocateBuffer(_frameBuffer01);
	AllocateBuffer(_frameBuffer02);

	AllocateBitMapInfo();

	Events::EngineEventManager::NotifyWindowResize();
}

double GEngine::EngineWindow::GetDeltaTime() const
{
	return _elapsedTime.count();
}

bool GEngine::EngineWindow::GetKeyDown(Utilities::KeyCode key)
{
	if(!isKeyHold && isKeyPressed && (GEngine::GetKeyState((int)key) & 0x8000))
	{
		isKeyPressed = false;
		isKeyHold = true;
		return true;
	}

	return false;
}

bool GEngine::EngineWindow::GetKey(Utilities::KeyCode key)
{
	if(GEngine::GetKeyState((int)key) & 0x8000)
	{
		isKeyHold = true;
		return true;
	}

	return false;
}

bool GEngine::EngineWindow::GetKeyUp(Utilities::KeyCode key)
{
	if(isKeyUp && !(GEngine::GetKeyState((int)key) & 0x8000))
	{
		isKeyUp = false;
		return true;
	}

	return false;
}
