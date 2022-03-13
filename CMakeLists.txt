cmake_minimum_required(VERSION 3.21)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "-municode")

add_executable(${PROJECT_NAME}
        GameApplication/main.cpp
        # ----- ECS Core -----
        Engine/src/GEngine/EcsCore/EntityManager.cpp
        Engine/src/GEngine/EcsCore/ComponentManager.cpp
        Engine/src/GEngine/EcsCore/System.cpp
        Engine/src/GEngine/EcsCore/EcsManager.cpp
        # ----- Game Engine -----
        Engine/src/GGraphics/GWindow/Window.cpp
        Engine/src/GEngine/GameWorld.cpp
        Engine/src/GEngine/GameEngine.cpp
        Engine/src/GGraphics/Mesh.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC
        "Engine/include/"
        "GameApplication/")

