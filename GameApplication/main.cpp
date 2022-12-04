#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"

#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/InputCon.h"
#include "ECS/Components/Transform.h"

#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/InputSystem.h"

bool isGameOver = false;
std::condition_variable cv;
std::mutex cv_m;

class Initiate
{
	private:
		// Delta time (Locked at 60 fps)
		// Fixed time step
		float dt = 1/60.;

	public: // Initial Requirements
		GEngine::GameEngine engine{};
		GEngine::GameWorld *world{};
		ECS::EcsManager *em{};

	public: // Entities
		ECS::EntityID cube{};

	public: // Systems
		std::unique_ptr<MoveSystem> ms{};
		std::unique_ptr<RenderSystem> rs{};

	public:
		Initiate()
		{
			Init();
		}
		~Initiate()= default;

	public:
		void Init()
		{
			world = engine.GetGameWorld();
			em = world->GetEcsManager();
			engine.CreateEngineWindow(800, 600, "GaggedEngine");

			CreateAndSetupEntities();

			SetListener();
		}

		void CreateAndSetupEntities()
		{
			std::cout << "Creating and Setting up entities...\n";

			CreateCubeEntity();

			std::cout << "Creating and Setting up entities done.\n";
		}

		void CreateCubeEntity()
		{
			cube = em->CreateEntity();
			em->SetEntityName(cube, "Default Cube");
			em->AssignComponent<Components::Transform>(cube);
			em->AssignComponent<Components::MeshComponent>(cube);

			Components::MeshComponent mc{};
			mc.mesh = *new GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Components::Transform>({
												{0, 0, 0},
											    {0, 0, 0},
											    {1, 1, 1}}, cube);
			em->SetComponentValue<Components::MeshComponent>(mc, cube);
		}

		void CreateAndSetupSystems(void* windowRef)
		{
			auto *pWindow = reinterpret_cast<GEngine::EngineWindow*>(windowRef);

			ms = std::make_unique<MoveSystem>("Move");
			ms->OnCreate(world, pWindow);

			rs = std::make_unique<RenderSystem>("Render");
			rs->OnCreate(world, pWindow);
		}

		void SetListener()
		{
			std::cout << "Setting up listeners...\n";

			EventManager::QuitGame.AddListener([](){
				isGameOver = true;
				cv.notify_all();
			});

			EventManager::WindowCreate.AddListener([this](void* windowRef){ CreateAndSetupSystems(windowRef); });

			EventManager::WindowUpdate.AddListener([this](double elapsedTime){ UpdateSystems(elapsedTime); });
		}

		void UpdateSystems(double elapsedTime) const
		{
			ms->OnUpdate(elapsedTime, world);

			// Render System
			// Always call at last so that every thing is rendered
			rs->OnUpdate(elapsedTime, world);
		}
};

int main()
{
	std::cout << "Main Thread ID :: " << std::this_thread::get_id() << "\n";

	Initiate initiate{};

	std::unique_lock<std::mutex> lk(cv_m);
	std::cerr << "Waiting on main thread... \n";
	cv.wait(lk, []{ return isGameOver; });
	std::cerr << "Main Exited!\n";

}
