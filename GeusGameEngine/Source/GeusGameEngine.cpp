#include "Engine.h"
#include "World.h"

#include <SDL.h>

int main(int argc, char* argv[])
{
	auto geusGameEngine = Engine::CreateAndInitialize();
		
	geusGameEngine->KickOff();

	return 0;
}