#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Renderer.h"
#include "ECS/Components/InputCon.h"

#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/InputSystem.h"

#include "EventManager.h"

// Function Prototypes
void TestFunc()
{
	std::cout << "Test action performed\n";
}

void TestFunc2()
{
	std::cout << "Test action 2 performed\n";
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	GEngine::GameEngine engine;

	auto world = engine.GetGameWorld();
	auto em = world->GetEcsManager();

	EventManager::TestAction.AddListener(TestFunc);
	EventManager::TestAction2.AddListener(TestFunc2);

	auto circleEnt = em->CreateEntity();
	em->SetEntityName(circleEnt, "Circle");
	em->AssignComponent<Renderer>(circleEnt);
	em->AssignComponent<Transform>(circleEnt);
	em->AssignComponent<InputControl>(circleEnt);

	em->SetComponentValue<Transform>({{400, 300, 0}}, circleEnt);
	em->SetComponentValue<Renderer>({Shape::Circle, 100},circleEnt);

	auto squareEnt = em->CreateEntity();
	em->SetEntityName(squareEnt, "Square");
	em->AssignComponent<Renderer>(squareEnt);
	em->AssignComponent<Transform>(squareEnt);
	em->AssignComponent<InputControl>(squareEnt);

	em->SetComponentValue<Transform>({{100, 200, 0}}, squareEnt);
	em->SetComponentValue<Renderer>({Shape::Square, 0, {{150, 120, 0}}},squareEnt);

	auto inputController = em->CreateEntity();
	em->SetEntityName(inputController, "UserInput");
	em->AssignComponent<InputControl>(inputController);

	// All the systems will be unique pointer as we only want 1 system for a particular task
	auto rs = std::make_unique<RenderSystem>("Render");
	rs->OnCreate(world);

	auto ms = std::make_unique<MoveSystem>("Move");
	ms->OnCreate(world);

	auto is = std::make_unique<InputSystem>("Input");
	is->OnCreate(world);


	// Delta time (Locked at 60 fps)
	// Fixed time step
	float dt = 1/60.f;

	// Perform a test action before starting render loop
	EventManager::NotifyTestActionPerformed("Main");

	while (true)
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