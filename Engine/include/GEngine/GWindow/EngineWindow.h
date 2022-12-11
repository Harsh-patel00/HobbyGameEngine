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

#ifndef GAMEENGINE_ENGINEWINDOW_H
#define GAMEENGINE_ENGINEWINDOW_H

#include <thread>
#include <condition_variable>

#include "BaseWindow.h"
#include "GGraphics/Color.h"
#include "Utilities/EngineEventManager.h"
#include "Utilities/VirtualKeys.h"

namespace GEngine
{
   class EngineWindow : public BaseWindow<EngineWindow>
   {
	   private:
		   int _windowWidth{}, _windowHeight{};
		   std::string _windowTitle{};
		   bool _isDefaultBufferActive = true;
		   void *_frameBuffer01{}; // Framebuffer stores pixel addresses
		   void *_frameBuffer02{}; // Second framebuffer is used for double buffering
		   BITMAPINFO _bitmapInfo{};
		   HDC _hdc{};
		   std::chrono::duration<double> _elapsedTime{};

		   bool _isWindowClosed = false;

	   public:
		   int GetWidth();
		   int GetHeight();

	   public:
		   EngineWindow() = default;
		   EngineWindow(int windowWidth, int windowHeight, std::string windowTitle);

		   ~EngineWindow();

		   PCWSTR  ClassName() const override { return L"Engine Window Class"; }
		   LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

		   void DrawPixel(int x, int y, GGraphics::Color = GGraphics::Color(GGraphics::ColorEnum::WHITE));
		   double GetDeltaTime() const;
		   bool GetKey(Utilities::KeyCode key);
		   bool GetKeyDown(Utilities::KeyCode key);
		   bool GetKeyUp(Utilities::KeyCode key);


	   private:
		   void Show();
		   void StartMessageLoop();

		   void InitBuffers();
		   // This assigns a memory of size _windowWidth*_windowHeight and stores in buffer
		   void AllocateBuffer(void *(&buffer)) const;
		   void DeallocateBuffer(void *(&buffer)) const;
		   void SetActiveBuffer(void *buffer);
		   void* GetActiveBuffer() const;
		   void AllocateBitMapInfo();
		   void SwapBuffers();
		   void OnUpdate();
		   void ColorPixel(int x, int y, GGraphics::Color color);
		   void ClearBg(GGraphics::Color = GGraphics::Color(GGraphics::ColorEnum::BLACK));

		   void HandleWindowResize(int newWidth, int newHeight);
   };
}
#endif //GAMEENGINE_ENGINEWINDOW_H
