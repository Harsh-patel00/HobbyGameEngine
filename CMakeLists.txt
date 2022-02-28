cmake_minimum_required(VERSION 3.21)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/GameApplication/main.cpp
        # ----- ECS Core -----
        src/GEngine/EcsCore/EntityManager.cpp
        src/GEngine/EcsCore/ComponentManager.cpp
        src/GEngine/EcsCore/System.cpp
        src/GEngine/EcsCore/EcsManager.cpp
        # ----- Game Engine -----
        src/GGraphics/GWindow/Window.cpp
        src/GEngine/GameWorld.cpp
        src/GEngine/GameEngine.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC
        "ExternalDependencies/BGI/include/"
        "./include/"
        "./src/GameApplication/")

target_link_directories(${PROJECT_NAME} PRIVATE "ExternalDependencies/BGI/lib/")
target_link_libraries(${PROJECT_NAME} libbgi.a)
