//
// Created by Harsh on 10-01-2022.
//

#include "GEngine/GameEngine.h"

std::unique_ptr<GEngine::GameWorld> GEngine::GameEngine::_world = std::make_unique<GEngine::GameWorld>(); // NOLINT(cert-err58-cpp)
