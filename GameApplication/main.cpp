#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"
#include "ECS/Components/InputCon.h"
#include "ECS/Components/GameObject.h"

#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/InputSystem.h"

#include "EventManager.h"

bool isGameOver = false;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	GEngine::GameEngine engine;

	auto world = engine.GetGameWorld();
	auto em = world->GetEcsManager();

	EventManager::QuitGame.AddListener([]()
	{
		isGameOver = true;
	});

	#pragma region Entities creation and components assignment

	auto circleEnt = em->CreateEntity();
	em->SetEntityName(circleEnt, "Circle");
	em->AssignComponent<GameObject>(circleEnt);
	em->AssignComponent<InputControl>(circleEnt);

	em->SetComponentValue<GameObject>({{{},{},{}},
									   {}}, circleEnt);

	auto inputController = em->CreateEntity();
	em->SetEntityName(inputController, "UserInput");
	em->AssignComponent<InputControl>(inputController);

	#pragma endregion

	#pragma region Systems creation and initialization

	// All the systems will be unique pointer as we only want 1 system for a particular task
	auto rs = std::make_unique<RenderSystem>("Render");
	rs->OnCreate(world);

	auto ms = std::make_unique<MoveSystem>("Move");
	ms->OnCreate(world);

	auto is = std::make_unique<InputSystem>("Input");
	is->OnCreate(world);

	#pragma endregion

	// Delta time (Locked at 60 fps)
	// Fixed time step
	float dt = 1/60.f;

	// Game Loop
	while(!isGameOver)
	{
		// Input System
		is->OnUpdate(dt, world);

		// Move System
		ms->OnUpdate(dt, world);

		// Render System
		// Always call at last so that every thing is rendered
		rs->OnUpdate(dt, world);
	}
}
#pragma clang diagnostic pop