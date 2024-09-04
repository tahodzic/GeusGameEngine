#pragma once

#include <SDL.h>
#include "Engine.h"
#include "World.h"

int main(int argc, char* argv[])
{
	auto geusGameEngine = Engine::CreateAndInitialize();
		
	geusGameEngine->KickOff();

	return 0;
}