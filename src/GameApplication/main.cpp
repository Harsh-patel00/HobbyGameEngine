#include <iostream>

#include "graphics.h"
#include "GEngine/GameEngine.h"

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

struct Transform
{
   float position{};
};

struct Renderer
{

};

struct Random0Comp
{
	float i{};
	int x{};
	Transform tr;
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	GEngine::GameEngine engine;

	auto world = engine.GetGameWorld();
	auto em = world->GetEntityManager();

	auto player = em->CreateEntity();
	em->SetEntityName(player, "Player");
	std::cout << "Total Entities : " << em->AliveEntityCount << "\n";

	auto enemy = em->CreateEntity();
	em->SetEntityName(enemy, "Enemy");
	std::cout << "Total Entities : " << em->AliveEntityCount << "\n";

	auto aiagent = em->CreateEntity();
	std::cout << "Total Entities : " << em->AliveEntityCount << "\n";

	em->ECS::EntityManager::AssignComponent<Transform>(player);
	em->ECS::EntityManager::AssignComponent<Renderer>(player);
	em->ECS::EntityManager::AssignComponent<Random0Comp>(player);

	em->ECS::EntityManager::AssignComponent<Transform>(enemy);
	em->ECS::EntityManager::AssignComponent<Random0Comp>(enemy);

	em->ECS::EntityManager::AssignComponent<Transform>(aiagent);
	em->ECS::EntityManager::AssignComponent<Renderer>(aiagent);
	
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