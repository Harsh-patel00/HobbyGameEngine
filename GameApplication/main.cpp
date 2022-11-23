#include <iostream>

// User-defined header files
#include "GEngine/GameEngine.h"
#include "GEngine/GWindow/EngineWindow.h"

#include "ECS/Components/Renderer.h"
#include "ECS/Components/InputCon.h"
#include "ECS/Components/GameObject.h"

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
		GEngine::EngineWindow *window{};

	public: // Entities
		ECS::EntityID circleEnt{};
		ECS::EntityID inputController{};

	public: // Systems
		std::unique_ptr<InputSystem> is{};
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


//			StartGameLoop();
		}


		void CreateAndSetupEntities()
		{
			std::cout << "Creating and Setting up entities...\n";
			circleEnt = em->CreateEntity();
			em->SetEntityName(circleEnt, "Circle");
			em->AssignComponent<GameObject>(circleEnt);
			em->AssignComponent<InputControl>(circleEnt);

			em->SetComponentValue<GameObject>({{{},{},{}},
			                                   {}}, circleEnt);

			inputController = em->CreateEntity();
			em->SetEntityName(inputController, "UserInput");
			em->AssignComponent<InputControl>(inputController);

			std::cout << "Creating and Setting up entities done.\n";
		}

		void CreateAndSetupSystems()
		{
			is = std::make_unique<InputSystem>("Input");
			is->OnCreate(world);

			ms = std::make_unique<MoveSystem>("Move");
			ms->OnCreate(world);

			rs = std::make_unique<RenderSystem>("Render");
			rs->OnCreate(world);
		}

		void SetListener()
		{
			std::cout << "Setting up listeners...\n";

			EventManager::QuitGame.AddListener([](){
				isGameOver = true;
				cv.notify_all();
			});
			EventManager::WindowUpdate.AddListener([this](void* windowRef){ UpdateSystems(windowRef); });
		}

		void UpdateSystems(void* windowRef)
		{
			std::cout << "Update systems called\n";

			is->OnUpdate(dt, world);
			ms->OnUpdate(dt, world);

			GEngine::EngineWindow *pWindow = reinterpret_cast<GEngine::EngineWindow*>(windowRef);

			// Render System
			// Always call at last so that every thing is rendered
			rs->OnUpdate(dt, world, pWindow);
		}

		void StartGameLoop()
		{
			using namespace std::literals::chrono_literals;
			while(!isGameOver)
			{
				std::cout << "Inside main game loop!\n";
				std::this_thread::sleep_for(1s);
			}
		}
};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main()
{
	std::cout << "Main Thread ID :: " << std::this_thread::get_id() << "\n";

	Initiate initiate{};

//	std::mutex worker1Mutex;
//
//	std::thread worker1([&](){
//
//		worker1Mutex.lock();
//
//		std::cout << "Worker 1 ID :: " << std::this_thread::get_id() << "\n";
//
//
//
//		worker1Mutex.unlock();
//	});

//	if(worker1.joinable())
//		worker1.join();

//	worker1.detach();

	std::unique_lock<std::mutex> lk(cv_m);
	std::cerr << "Waiting on main thread... \n";
	cv.wait(lk, []{ return isGameOver; });
	std::cerr << "Main Exited!\n";

}
#pragma clang diagnostic pop
