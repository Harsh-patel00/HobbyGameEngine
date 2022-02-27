cmake_minimum_required(VERSION 3.21)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

link_directories(GameEngine "ExternalDependencies/BGI/lib/")

include_directories(GameEngine
        "ExternalDependencies/BGI/include/"
        "./include/"
        "./src/GameApplication/")

add_executable(GameEngine
        src/GameApplication/main.cpp
        # ----- ECS Core -----
        src/GEngine/EcsCore/EntityManager.cpp
        src/GEngine/EcsCore/ComponentManager.cpp
        src/GEngine/EcsCore/System.cpp
        src/GEngine/EcsCore/EcsManager.cpp
        # ----- Game Engine -----
        src/GGraphics/GWindow/Window.cpp
        src/GEngine/GameWorld.cpp
        src/GEngine/GameEngine.cpp
        # ----- ECS Components -----
        src/GameApplication/ECS/Components/Transform.cpp
        src/GameApplication/ECS/Components/Renderer.cpp
        src/GameApplication/ECS/Components/InputCon.cpp
        # ----- ECS Systems -----
        src/GameApplication/ECS/Systems/src/InputSystem.cpp)



target_link_libraries(GameEngine libbgi.a)
