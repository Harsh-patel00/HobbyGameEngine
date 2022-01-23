#include <iostream>

// User-defined header files
#include "graphics.h"
#include "GEngine/GameEngine.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"

#include "ECS/Systems/RenderSystem.h"

enum class ShapeType
{
	CIRCLE = 0,
	LINE   = 1
};

// Function Prototypes
void Draw(ShapeType);

void CheckKeys();

void SwapBuffers();

void CheckMouse();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	GEngine::GameEngine engine;

	auto world = engine.GetGameWorld();
	auto em = world->GetEcsManager();

	auto player = em->CreateEntity();
	em->SetEntityName(player, "Player");
	std::cout << "Total Entities : " << em->GetAliveEntityCount() << "\n";

	auto enemy = em->CreateEntity();
	em->SetEntityName(enemy, "Enemy");
	std::cout << "Total Entities : " << em->GetAliveEntityCount() << "\n";

	auto aiagent = em->CreateEntity();
	em->SetEntityName(aiagent, "AI_Agent");
	std::cout << "Total Entities : " << em->GetAliveEntityCount() << "\n";

	em->AssignComponent<Transform>(player);
	em->AssignComponent<Renderer>(player);

	em->AssignComponent<Transform>(enemy);

	em->AssignComponent<Transform>(aiagent);
	em->AssignComponent<Renderer>(aiagent);

	auto rs = std::make_unique<RenderSystem>("Render");

	while (true)
	{
		CheckKeys();

		rs->OnUpdate(1/60.f, em);
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

void Draw(ShapeType type)
{
	switch (type)
	{
		case ShapeType::CIRCLE:
			circle(getmaxwidth()/2, getmaxheight()/2, 100);
			break;
		case ShapeType::LINE:
			//line(x1y1.x, x1y1.y, x1y1.x + 100, x1y1.y);
			break;
	}
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
			// CirclePos.x += 5;
			// x1y1.x += 5;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			// CirclePos.x -= 5.f;
			// x1y1.x -= 5;
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