//
// Created by Harsh on 20-01-2022.
//

#include "GEngine/ECS/System.h"

ECS::System::System(int sid)
{
	systemId = sid;
	Init();
}

void ECS::System::Init()
{
}

ECS::System::~System()
{

}

void ECS::System::OnUpdate(float dt)
{
	std::cout << "Base OnUpdate...\n";
}

void ECS::System::Run()
{
	while(true)
	{
		OnUpdate(1/60.f);
	}
}

