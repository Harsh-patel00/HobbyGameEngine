//
// Created by Harsh on 20-01-2022.
//

#include "GEngine/EcsCore/System.h"

ECS::System::System(const std::string &name)
{
	Init(name);
}

void ECS::System::Init(const std::string &name)
{
	std::cout << "Initializing " << name << " System...\n";
}

ECS::System::~System()
{

}
