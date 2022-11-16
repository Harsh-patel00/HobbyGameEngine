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

//#include <ggraphics.h> // TODO: Write this header file
#include <thread>

#include "BaseWindow.h"
#include "GEngine/Action.h"

namespace GEngine
{
   class EngineWindow : public BaseWindow<EngineWindow>
   {
	   private:
		   // Run the update loop on a separate thread, so that rendering does not block the main thread.
		   std::thread _windowUpdateThread;

		   int _windowWidth{}, _windowHeight{};
		   bool _isDefaultBufferActive = true;
		   void *_frameBuffer01{}; // Framebuffer stores pixel addresses
		   void *_frameBuffer02{}; // Second framebuffer is used for double buffering
		   BITMAPINFO _bitmapInfo{};
		   HDC _hdc{};

		   bool _isWindowClosed = false;

	   public:
		   static Action<> WindowClosed;

	   public:
		   EngineWindow() = default;
		   EngineWindow(int windowWidth, int windowHeight, const wchar_t *windowTitle);

		   ~EngineWindow();

		   PCWSTR  ClassName() const override { return L"Engine Window Class"; }
		   LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	   private:
		   void Show();
		   void StartMessageLoop();
		   void UpdateOnSeparateThread();

		   void InitBuffers();
		   // This assigns a memory of size _windowWidth*_windowHeight and stores in buffer
		   void AllocateBuffer(void *(&buffer)) const;
		   void DeallocateBuffer(void *(&buffer)) const;
		   void SetActiveBuffer(void *buffer);
		   void* GetActiveBuffer() const;
		   void AllocateBitMapInfo();
		   void SwapBuffers();
		   void OnUpdate();
   };
}
#endif //GAMEENGINE_ENGINEWINDOW_H
