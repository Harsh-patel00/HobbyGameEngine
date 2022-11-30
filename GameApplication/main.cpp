#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"
#include "GEngine/GWindow/EngineWindow.h"

#include "ECS/Components/MeshComponent.h"
#include "ECS/Components/InputCon.h"
#include "ECS/Components/Transform.h"

#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/MoveSystem.h"
#include "ECS/Systems/InputSystem.h"
#include "GMath/Matrix4x4.h"

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
		GEngine::EngineWindow *window{};

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
			using namespace std::chrono_literals;

			world = engine.GetGameWorld();
			em = world->GetEcsManager();
			window = engine.GetEngineWindow();

			CreateAndSetupEntities();
			CreateAndSetupSystems();

			SetListener();
		}

		void CreateAndSetupEntities()
		{
			std::cout << "Creating and Setting up entities...\n";
			cube = em->CreateEntity();
			em->SetEntityName(cube, "Default Cube");
			em->AssignComponent<Transform>(cube);
			em->AssignComponent<MeshComponent>(cube);

			MeshComponent mc{};
			mc.mesh = *new GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Transform>({
												{10, 5, 3},
											    {0, 0, 0},
											    {1, 1, 1}}, cube);
			em->SetComponentValue<MeshComponent>(mc, cube);

			std::cout << "Creating and Setting up entities done.\n";
		}

		void CreateAndSetupSystems()
		{
			ms = std::make_unique<MoveSystem>("Move");
			ms->OnCreate(world);
		}

		void CreateRenderSystem(void* windowRef)
		{
			rs = std::make_unique<RenderSystem>("Render");

			auto *pWindow = reinterpret_cast<GEngine::EngineWindow*>(windowRef);

			rs->OnCreate(world, pWindow);
		}

		void SetListener()
		{
			std::cout << "Setting up listeners...\n";

			EventManager::QuitGame.AddListener([](){
				isGameOver = true;
				cv.notify_all();
			});

			EventManager::WindowCreate.AddListener([this](void* windowRef){ CreateRenderSystem(windowRef); });

			EventManager::WindowUpdate.AddListener([this](void* windowRef, double elapsedTime){ UpdateSystems(windowRef, elapsedTime); });

		}

		void UpdateSystems(void* windowRef, double elapsedTime)
		{
			ms->OnUpdate(elapsedTime, world);

			auto *pWindow = reinterpret_cast<GEngine::EngineWindow*>(windowRef);

			// Render System
			// Always call at last so that every thing is rendered
			rs->OnUpdate(elapsedTime, world, pWindow);
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
