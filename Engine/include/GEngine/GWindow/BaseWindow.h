//
// Created by Harsh on 10/11/2022.
//

#ifndef GAMEENGINE_BASEWINDOW_H
#define GAMEENGINE_BASEWINDOW_H

namespace GEngine
{

#include <Windows.h>

// Abstract base class
   template<class DERIVED_TYPE>
   class BaseWindow
   {
	   public:
		   static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		   {
			   DERIVED_TYPE *pThis = nullptr;

			   if(uMsg == WM_NCCREATE)
			   {
				   CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
				   pThis = reinterpret_cast<DERIVED_TYPE *>(pCreate->lpCreateParams);
				   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pThis);

				   pThis->m_hwnd = hwnd;
			   }
			   else
			   {
				   pThis = reinterpret_cast<DERIVED_TYPE *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			   }

			   if(pThis)
			   {
				   return pThis->HandleMessage(uMsg, wParam, lParam);
			   }
			   else
			   {
				   return DefWindowProc(hwnd, uMsg, wParam, lParam);
			   }
		   }

		   BaseWindow() : m_hwnd(nullptr)
		   {}

		   BOOL Create(PCWSTR lpWindowName,
		               int nWidth = CW_USEDEFAULT,
		               int nHeight = CW_USEDEFAULT,
		               DWORD dwStyle = WS_OVERLAPPEDWINDOW,
		               DWORD dwExStyle = 0,
		               int x = CW_USEDEFAULT,
		               int y = CW_USEDEFAULT,
		               HWND hWndParent = nullptr,
		               HMENU hMenu = nullptr)
		   {
			   WNDCLASSW wc = {0};

			   wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
			   wc.hInstance = GetModuleHandle(nullptr);
			   wc.lpszClassName = ClassName();

			   RegisterClassW(&wc);

			   RECT rect = {0, 0, nWidth, nHeight};
			   AdjustWindowRect(&rect, dwStyle, false);

			   m_hwnd = CreateWindowExW
					   (
							   dwExStyle,
							   ClassName(),
							   lpWindowName,
							   dwStyle,
							   x, y, // Starting position of window (w.r.t screen coords)
							   rect.right - rect.left, rect.bottom - rect.top,
							   hWndParent,
							   hMenu,
							   GetModuleHandle(nullptr),
							   this
					   );

			   return (m_hwnd ? TRUE : FALSE);
		   }

		   HWND Window() const
		   { return m_hwnd; }

	   protected:

		   virtual PCWSTR ClassName() const = 0;

		   virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

		   HWND m_hwnd;
   };

} // GameEngine

#endif //GAMEENGINE_BASEWINDOW_H
