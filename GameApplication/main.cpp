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
		ECS::EntityID cube2{};
		ECS::EntityID cube3{};
		ECS::EntityID cube4{};

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
			world = engine.GetGameWorld();
			em = world->GetEcsManager();

			CreateAndSetupEntities();
			SetListener();

			// Create window at last.
			// Threading might cause it to create earlier causing entities to not show up.
			engine.CreateEngineWindow(800, 600, "GaggedEngine");
		}

		void CreateAndSetupEntities()
		{
			std::cout << "Creating and Setting up entities...\n";

			//CreateCubeEntity();
			CreateCube2Entity();
			//CreateCube3Entity();
			//CreateCube4Entity();

			std::cout << "Creating and Setting up entities done.\n";
		}

		void CreateCubeEntity()
		{
			std::cout << "Creating a cube entity...\n";

			cube = em->CreateEntity();
			em->SetEntityName(cube, "Default Cube 1");
			em->AssignComponent<Components::Transform>(cube);
			em->AssignComponent<Components::MeshComponent>(cube);

			Components::MeshComponent mc{};

			std::vector<Point3f> verts{
				//Point3f(0, 0, 0),
				//Point3f(0, 0, 1),
				//Point3f(0.5f, 0, 1.5f),
				//Point3f(1, 0, 1),
				//Point3f(1, 0, 0)
				Point3f(-0.5f, 0, 0),
				Point3f(0, 0.5f, 0),
				Point3f(0.5f, 0, 0)
			};

			std::vector<int> indices{ 0, 1, 2 };

			//mc.mesh = GGraphics::Mesh(verts, indices, GGraphics::MeshDrawMode::Triangle);
			mc.mesh = GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Components::Transform>({
												{-2, 0, 0},
											    {0, 0, 0},
											    {1, 1, 1}}, cube);
			em->SetComponentValue<Components::MeshComponent>(mc, cube);
		}

		void CreateCube2Entity()
		{
			cube2 = em->CreateEntity();
			em->SetEntityName(cube2, "Default Cube 2");
			em->AssignComponent<Components::Transform>(cube2);
			em->AssignComponent<Components::MeshComponent>(cube2);
			em->AssignComponentAndSetDefaultValues<Components::InputControl>(cube2);

			Components::MeshComponent mc{};
			mc.mesh = GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Components::Transform>({
												{0, 0, 0},
											    {0, 0, 0},
											    {1, 1, 1}}, cube2);
			em->SetComponentValue<Components::MeshComponent>(mc, cube2);
		}

		void CreateCube3Entity()
		{
			cube3 = em->CreateEntity();
			em->SetEntityName(cube3, "Default Cube 3");
			em->AssignComponent<Components::Transform>(cube3);
			em->AssignComponent<Components::MeshComponent>(cube3);

			Components::MeshComponent mc{};
			mc.mesh = GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Components::Transform>({
												{2, 0, 0},
											    {0, 0, 0},
											    {1, 1, 1}}, cube3);
			em->SetComponentValue<Components::MeshComponent>(mc, cube3);
		}

		void CreateCube4Entity()
		{
			cube4 = em->CreateEntity();
			em->SetEntityName(cube4, "Default Cube 4");
			em->AssignComponent<Components::Transform>(cube4);
			em->AssignComponent<Components::MeshComponent>(cube4);

			Components::MeshComponent mc{};
			mc.mesh = GGraphics::Mesh(GGraphics::PRIMITIVE3DTYPE::Cube);

			em->SetComponentValue<Components::Transform>({
												{0, -2, 0},
											    {0, 0, 0},
											    {1, 1, 1}}, cube4);
			em->SetComponentValue<Components::MeshComponent>(mc, cube4);
		}

		void CreateAndSetupSystems(void* windowRef)
		{
			auto *pWindow = reinterpret_cast<GEngine::EngineWindow*>(windowRef);

			is = std::make_unique<InputSystem>("Input");
			is->OnCreate(world, pWindow);

			ms = std::make_unique<MoveSystem>("Move");
			ms->OnCreate(world, pWindow);

			rs = std::make_unique<RenderSystem>("Render");
			rs->OnCreate(world, pWindow);
		}

		void SetListener()
		{
			std::cout << "Setting up listeners...\n";

			Events::EngineEventManager::WindowClosed.AddListener([](){
				isGameOver = true;
				cv.notify_all();
			});

			Events::EngineEventManager::WindowCreate.AddListener([this](void* windowRef){ CreateAndSetupSystems(windowRef); });

			Events::EngineEventManager::WindowUpdate.AddListener([this](double elapsedTime){ UpdateSystems(elapsedTime); });
		}

		void UpdateSystems(double elapsedTime) const
		{
			if(is != nullptr)
			{
				is->OnUpdate(elapsedTime, world);
			}

			if(ms != nullptr)
			{
				ms->OnUpdate(elapsedTime, world);
			}

			if(rs != nullptr)
			{
				// Render System
				// Always call at last so that every thing is rendered
				rs->OnUpdate(elapsedTime, world);
			}
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

	return 0;
}
