#pragma once

#include <SDL.h>
#include "World.h"

int main(int argc, char* argv[])
{
	auto myWorld = World::CreateAndInitialize();
		
	for(;;)
	{
		myWorld.HandleAction();
		myWorld.Render();
	}

	return 0;
}