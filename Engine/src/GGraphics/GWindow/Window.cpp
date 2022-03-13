//
// Created by Harsh on 10-01-2022.
//

#include "GGraphics/GWindow/Window.h"

Action<> GGraphics::Window::WindowClosed{};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

GGraphics::Window::Window(int windowWidth, int windowHeight, const wchar_t *windowTitle)
{

	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	_windowClassName = L"GameWindow";
	_windowName = windowTitle;

	WNDCLASSEXW wc{};

	wc.cbSize = sizeof (WNDCLASSEXW);
	wc.lpszClassName = _windowClassName;
	wc.lpfnWndProc = WindowProc;

	assert(RegisterClassExW(&wc));

	RECT rect = {0, 0, windowWidth, windowHeight};
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);


	_windowHandle = CreateWindowExW(0,
									_windowClassName,
									_windowName,
									WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
									0,0, // Starting position of window (w.r.t screen coords)
									rect.right - rect.left, rect.bottom - rect.top,
									nullptr, nullptr, nullptr, nullptr
									);

	assert(_windowHandle);

	AllocateMemory();
	AllocateBitMapInfo();
	_hdc = GetDC(_windowHandle);

	ShowWindow(_windowHandle, SW_SHOW);
	UpdateWindow(_windowHandle);

	// TODO: Move this function to proper location (probably OnCreate())
	// Set background color once
	SetBkColor({40, 40, 40});
}

GGraphics::Window::~Window()
{
	// Destruction of windows
	DestroyWindow(_windowHandle);
	_windowHandle = nullptr;
}

// This will be called inside a loop
void GGraphics::Window::Broadcast()
{
	MSG msg{};
	if(PeekMessageW(&msg, _windowHandle, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	OnUpdate();
}

void GGraphics::Window::PrintWindowDims()
{
	RECT rect{};
	GetClientRect(_windowHandle, &rect);

	std::cout << "Window dims mentioned : (" << _windowWidth << ", " << _windowHeight << ")\n";
	std::cout << "Window dims : (" << rect.right - rect.left << ", " << rect.bottom - rect.top << ")\n";
}

void GGraphics::Window::AllocateMemory()
{
	_windowMemory = VirtualAlloc(
			nullptr,
			// Because we want size of memory as big as screen size
			// as we are storing all pixels (each of size 4 bytes)
			_windowWidth * _windowHeight * sizeof (uint32_t),
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);
}

void GGraphics::Window::AllocateBitMapInfo()
{
	_bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
	_bitmapInfo.bmiHeader.biWidth = _windowWidth;
	_bitmapInfo.bmiHeader.biHeight = _windowHeight;
	_bitmapInfo.bmiHeader.biPlanes = 1;
	_bitmapInfo.bmiHeader.biBitCount = 32;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

void GGraphics::Window::OnUpdate()
{
	for (int i = 0; i < 255; ++i)
	{
		DrawPixel(i, i*2, {static_cast<uint32_t>(i),
							                static_cast<uint32_t>(i+1),
							                static_cast<uint32_t>(i+3)});
	}
}

void GGraphics::Window::DrawPixel(int x, int y, GColor newColor)
{
	ColorPixel(x, y, newColor);

	StretchDIBits(_hdc,
	              0, // This means whole client area
	              0, // This means whole client area
	              _windowWidth,
	              _windowHeight,
	              0,
	              0,
	              _windowWidth,
	              _windowHeight,
	              _windowMemory,
	              &_bitmapInfo,
	              DIB_RGB_COLORS,
	              SRCCOPY
	             );
}

void GGraphics::Window::ColorPixel(int x, int y, GGraphics::GColor newColor)
{
	auto *pixel = (uint32_t *)_windowMemory;

	uint32_t color = (newColor.r << 16) ^ (newColor.g << 8) ^ newColor.b;

	if(x == _windowWidth)
		x--;

	if(y == _windowHeight)
		y--;

	pixel += y * _windowWidth + x; // Travel up by y, window width times + move forward by x

	*pixel = color;
}

void GGraphics::Window::SetBkColor(GGraphics::GColor bkColor)
{
	auto *pixel = (uint32_t *)_windowMemory;

	uint32_t color = (bkColor.r << 16) ^ (bkColor.g << 8) ^ bkColor.b;

	for (int i = 0; i < _windowWidth * _windowHeight; ++i)
	{
		*pixel++ = color;
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			std::cout << "Window is created!\n";
			break;
		}

		case WM_PAINT:
		{
//			PAINTSTRUCT ps;
//			HDC hdc = BeginPaint(hwnd, &ps);
//
//			// All painting occurs here, between BeginPaint and EndPaint.
//
//			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW));
//
//			EndPaint(hwnd, &ps);

			break;
		}

		case WM_DESTROY:
		{
			std::cout << "Window is destroyed!\n";
			GGraphics::Window::WindowClosed.Invoke("WindowClosed");
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

