#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"

#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MoveSystem.h"

// Function Prototypes
void CheckKeys();

void CheckMouse();

void SwapBuffers();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	GEngine::GameEngine engine;

	auto world = engine.GetGameWorld();
	auto em = world->GetEcsManager();

	auto circleEnt = em->CreateEntity();
	em->SetEntityName(circleEnt, "Circle");
	em->AssignComponent<Renderer>(circleEnt);
	em->AssignComponent<Transform>(circleEnt);

	em->SetComponentValue<Transform>({{400, 300, 0}}, circleEnt);
	em->SetComponentValue<Renderer>({Shape::Circle, 100},circleEnt);

	auto squareEnt = em->CreateEntity();
	em->SetEntityName(squareEnt, "Square");
	em->AssignComponent<Renderer>(squareEnt);
	em->AssignComponent<Transform>(squareEnt);

	em->SetComponentValue<Transform>({{100, 200, 0}}, squareEnt);
	em->SetComponentValue<Renderer>({Shape::Square, 0, {{150, 120, 0}}},squareEnt);

	auto rs = std::make_unique<RenderSystem>("Render");
	auto ms = std::make_unique<MoveSystem>("Move");
	rs->OnCreate(em);
	ms->OnCreate(em);

	// Delta time (Locked at 60 fps)
	// Fixed time step
	float dt = 1/60.f;

	while (true)
	{
		CheckKeys();
		CheckMouse();

		ms->OnUpdate(dt, em);

		// Always call at last before SwapBuffers
		rs->OnUpdate(dt, em);
		SwapBuffers();
	}
}
#pragma clang diagnostic pop

// Function Defs
void CheckMouse()
{
	int mousePosX = 0;
	int mousePosY = 0;

	// On mouse move
	if(ismouseclick(WM_MOUSEMOVE))
	{
		getmouseclick(WM_MOUSEMOVE, mousePosX, mousePosY);
		clearmouseclick(WM_MOUSEMOVE);
	}

	#pragma region LeftButton

	if(ismouseclick(WM_LBUTTONDOWN))
	{
		getmouseclick(WM_LBUTTONDOWN, mousePosX, mousePosY);

		showerrorbox("Mouse Clicked!");

		clearmouseclick(WM_LBUTTONDOWN);
	}
	if(ismouseclick(WM_LBUTTONUP))
	{
		getmouseclick(WM_LBUTTONUP, mousePosX, mousePosY);
		clearmouseclick(WM_LBUTTONUP);
	}
	if(ismouseclick(WM_LBUTTONDBLCLK))
	{
		getmouseclick(WM_LBUTTONDBLCLK, mousePosX, mousePosY);
		clearmouseclick(WM_LBUTTONDBLCLK);
	}

	#pragma endregion

	#pragma region RightButton

	if(ismouseclick(WM_RBUTTONDOWN))
	{
		getmouseclick(WM_RBUTTONDOWN, mousePosX, mousePosY);
		clearmouseclick(WM_RBUTTONDOWN);
	}
	if(ismouseclick(WM_RBUTTONUP))
	{
		getmouseclick(WM_RBUTTONUP, mousePosX, mousePosY);
		clearmouseclick(WM_RBUTTONUP);
	}
	if(ismouseclick(WM_RBUTTONDBLCLK))
	{
		getmouseclick(WM_RBUTTONDBLCLK, mousePosX, mousePosY);
		clearmouseclick(WM_RBUTTONDBLCLK);
	}

	#pragma endregion

	#pragma region MiddleButton

	if(ismouseclick(WM_MBUTTONDOWN))
	{
		getmouseclick(WM_MBUTTONDOWN, mousePosX, mousePosY);
		clearmouseclick(WM_MBUTTONDOWN);
	}
	if(ismouseclick(WM_MBUTTONUP))
	{
		getmouseclick(WM_MBUTTONUP, mousePosX, mousePosY);
		clearmouseclick(WM_MBUTTONUP);
	}
	if(ismouseclick(WM_MBUTTONDBLCLK))
	{
		getmouseclick(WM_MBUTTONDBLCLK, mousePosX, mousePosY);
		clearmouseclick(WM_MBUTTONDBLCLK);
	}

	#pragma endregion
}

void CheckKeys()
{
	if (kbhit() == true)
	{
		if ( GetAsyncKeyState(VK_ESCAPE) || char(toupper(getch())) == 'Q' )
		{
			std::cout << "Exiting...\n";

			exit(EXIT_SUCCESS);
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{

		}

		if (GetAsyncKeyState(VK_LEFT))
		{

		}

		if(char(toupper(getch())) == 'G')
		{

		}
	}
}

void SwapBuffers()
{
	// Double Buffering
	setactivepage(getvisualpage());
	setvisualpage(!getactivepage());
	clearviewport();
}