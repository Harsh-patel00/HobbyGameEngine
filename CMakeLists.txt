cmake_minimum_required(VERSION 3.21)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

link_directories(GameEngine "ExternalDependencies\\lib\\")

add_executable(GameEngine src/GameApplication/main.cpp
        src/GGraphics/GWindow/Window.cpp
        include/GEngine/GameWorld.h
        src/GEngine/GameWorld.cpp
        include/GEngine/GameEngine.h
        src/GEngine/GameEngine.cpp
        include/GEngine/EcsCore/Prerequisite.h
        include/GEngine/EcsCore/EntityManager.h
        src/GEngine/EcsCore/EntityManager.cpp
        src/GEngine/EcsCore/ComponentManager.cpp
        include/GEngine/EcsCore/ComponentManager.h
        include/GEngine/EcsCore/System.h
        src/GEngine/EcsCore/System.cpp
        src/GEngine/EcsCore/EcsManager.cpp
        include/GEngine/EcsCore/EcsManager.h
        src/GameApplication/ECS/Components/Transform.h
        src/GameApplication/ECS/Components/Renderer.h
        src/GameApplication/ECS/Systems/RenderSystem.h
        src/GameApplication/ECS/Systems/MoveSystem.h
        src/GameApplication/ECS/Systems/InputSystem.h
        include/GEngine/Action.h
#        src/GEngine/Action.cpp
        src/GameApplication/EventManager.h
        src/GameApplication/ECS/Components/InputCon.h)

include_directories(GameEngine "ExternalDependencies\\include\\" "include\\" "src\\GameApplication\\")

target_link_libraries(GameEngine libbgi.a)
