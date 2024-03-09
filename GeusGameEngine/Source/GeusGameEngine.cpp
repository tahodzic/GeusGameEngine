#pragma once

#include "World.h"

int main(int argc, char* argv[])
{
		World myWorld;

		myWorld.Initialize();

		//auto cube2 = myWorld.CreateCube(0.5f, 05.0f, 0.0f, 0.0f);
		//auto cube3 = myWorld.CreateCube(0.5f, 10.0f, 0.0f, 0.0f);
		//auto cube4 = myWorld.CreateCube(0.5f, 15.0f, 0.0f, 0.0f);
		//auto cube5 = myWorld.CreateCube(0.5f, 25.0f, 0.0f, 0.0f);
		//auto cube6 = myWorld.CreateCube(0.5f, 30.0f, 0.0f, 0.0f);
		//auto cube7 = myWorld.CreateCube(0.5f, 35.0f, 0.0f, 0.0f);
		//auto cube8 = myWorld.CreateCube(0.5f, 40.0f, 0.0f, 0.0f);
		
		//myWorld.AddObject(cube2);
		//myWorld.AddObject(cube3);
		//myWorld.AddObject(cube4);
		//myWorld.AddObject(cube5);
		//myWorld.AddObject(cube6);
		//myWorld.AddObject(cube7);
		//myWorld.AddObject(cube8);
		
		for(;;)
		{
			myWorld.HandleAction();
			myWorld.Render();
		}

	return 0;
}