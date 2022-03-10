//
// Created by Harsh on 10-01-2022.
//

#include "GGraphics/GWindow/Window.h"

Action<> GGraphics::Window::WindowClosed{};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

GGraphics::Window::Window(int windowWidth, int windowHeight, const wchar_t *windowTitle)
{
	_windowClassName = L"GameWindow";
	_windowName = windowTitle;

	WNDCLASSEXW wc{};

	wc.cbSize = sizeof (WNDCLASSEXW);
	wc.lpszClassName = _windowClassName;
	wc.lpfnWndProc = WindowProc;

	assert(RegisterClassExW(&wc));

	RECT rect = {0, 0, windowWidth, windowHeight};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);


	_windowHandle = CreateWindowExW(0,
									_windowClassName,
									_windowName,
									WS_OVERLAPPEDWINDOW,
									CW_USEDEFAULT,CW_USEDEFAULT, windowWidth, windowHeight,
									nullptr, nullptr, nullptr, nullptr
									);

	assert(_windowHandle);

	ShowWindow(_windowHandle, SW_SHOW);
	UpdateWindow(_windowHandle);
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
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW));

			EndPaint(hwnd, &ps);

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

