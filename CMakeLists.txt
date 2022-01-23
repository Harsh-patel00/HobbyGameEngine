cmake_minimum_required(VERSION 3.21)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

link_directories(GameEngine "ExternalDependencies\\lib\\")

add_executable(GameEngine src/GameApplication/main.cpp
        src/GGraphics/GWindow/Window.cpp
        src/GGraphics/Draw.cpp
        include/GGraphics/Draw.h
        include/GGraphics/Shape.h
        src/GEngine/GameObject.cpp
        include/GEngine/GameObject.h
        include/GEngine/GameWorld.h
        src/GEngine/GameWorld.cpp
        include/GEngine/GameEngine.h
        src/GEngine/GameEngine.cpp
        include/GEngine/ECS/Prerequisite.h
        include/GEngine/ECS/EntityManager.h
        src/GEngine/ECS/EntityManager.cpp
        src/GEngine/ECS/ComponentManager.cpp
        include/GEngine/ECS/ComponentManager.h
        src/GEngine/ECS/SystemManager.cpp
        include/GEngine/ECS/SystemManager.h
        include/GEngine/ECS/System.h src/GEngine/ECS/System.cpp include/GEngine/ECS/EcsManager.cpp include/GEngine/ECS/EcsManager.h)

include_directories(GameEngine "ExternalDependencies\\include\\" "include\\" "src\\GameApplication")

target_link_libraries(GameEngine libbgi.a)
