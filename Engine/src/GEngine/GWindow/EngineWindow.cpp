//
// Created by Harsh on 03/11/2022.
//

#include <iostream>

#include "GEngine/GWindow/EngineWindow.h"
#include "GEngine/Action.h"

Action<> GEngine::EngineWindow::WindowClosed{};

GEngine::LRESULT GEngine::EngineWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			std::cout << "Window is Destroyed!!\nStop the execution of the program...\n";
//			WindowClosed.Invoke("WindowClosed");
			GEngine::EngineWindow::WindowClosed.Invoke("WindowClosed");
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

	Create(windowTitle, windowWidth, windowHeight);

	InitBuffers();
	AllocateBitMapInfo();
	_hdc = GEngine::GetDC(Window());

	Show();
}

void GEngine::EngineWindow::Show()
{
	std::cout << "Now showing window....\n";
	GEngine::ShowWindow(Window(), SW_SHOW);

	UpdateOnSeparateThread();

	// Starting message loop after update because message loop will block the thread
	StartMessageLoop();
}

void GEngine::EngineWindow::StartMessageLoop()
{
	std::cout << "\nListening for window messages...\n";
	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void GEngine::EngineWindow::OnUpdate()
{
	while(!_isWindowClosed)
	{
//		std::cout << "Inside update loop! \n";
		SwapBuffers();
	}
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
		DeallocateBuffer(_frameBuffer01);
//		_frameBuffer01 = nullptr;
		AllocateBuffer(_frameBuffer01);
		SetActiveBuffer(_frameBuffer02);
		_isDefaultBufferActive = false;
	}
	else
	{
		_frameBuffer01 = _frameBuffer02;
		DeallocateBuffer(_frameBuffer02);
//		_frameBuffer02 = nullptr;
		AllocateBuffer(_frameBuffer02);
		SetActiveBuffer(_frameBuffer01);
		_isDefaultBufferActive = true;
	}
}

void GEngine::EngineWindow::UpdateOnSeparateThread()
{
	_windowUpdateThread = std::thread([this](){
		std::cout << "\nRunning update...\n";
		OnUpdate();
	});

	std::cout << "Window update running on thread :: " << _windowUpdateThread.get_id() << "\n";

	_windowUpdateThread.detach();
}

GEngine::EngineWindow::~EngineWindow()
{
	_windowUpdateThread.detach();
	DeallocateBuffer(_frameBuffer01);
	DeallocateBuffer(_frameBuffer02);
	ReleaseDC(Window(), _hdc);
}
