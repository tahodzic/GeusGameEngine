#pragma once

#include "Constants.h"
#include "World.h"

int main(int argc, char* argv[])
{

		World myWorld;

		myWorld.init();

		float offset = (static_cast<float>(Constants::pi) / 4.0);
		float a = 0.0f;
		float b = 1.0f * offset;
		float c = 2.0f * offset;
		float d = 3.0f * offset;
		float e = 4.0f * offset;
		float f = 5.0f * offset;
		float g = 6.0f * offset;
		float h = 7.0f * offset;

		//Cube worldCenter(1,		0,		0,	0);
		//Cube myCube(1,			10,		0,	-10.0);
		//Cube myCube1_5(1,		6.7,	0,	-6.7);
		//Cube myCube2(1,			0,		0,	-20.0);
		//Cube myCube2_5(1,		6.7,	0,	-16.7);
		//Cube myCube3(1,			-10,	0,  -10.0);
		//Cube myCube3_5(1,		-6.7,	0,  -6.7);
		//myWorld.add_object(&worldCenter);
		//myWorld.add_object(&myCube);
		//myWorld.add_object(&myCube1_5);
		//myWorld.add_object(&myCube2);
		//myWorld.add_object(&myCube2_5);
		//myWorld.add_object(&myCube3);
		//myWorld.add_object(&myCube3_5);

		//Cube cubeRot1(1,	cos(a)*5, 0,	sin(a)*5);
		//Cube cubeRot1_5(1,	cos(b)*5, 0,	sin(b)*5);
		//Cube cubeRot2(1,	cos(c)*5, 0,	sin(c)*5);
		//Cube cubeRot2_5(1,	cos(d)*5, 0,	sin(d)*5);
		//Cube cubeRot3(1,	cos(e)*5, 0,	sin(e)*5);
		//Cube cubeRot3_5(1,	cos(f)*5, 0,	sin(f)*5);
		//Cube cubeRot4(1,	cos(g)*5, 0,	sin(g)*5);
		//Cube cubeRot4_5(1,	cos(h)*5, 0,	sin(h)*5);


		//myWorld.add_object(&cubeRot1);
		//myWorld.add_object(&cubeRot1_5);
		//myWorld.add_object(&cubeRot2);
		//myWorld.add_object(&cubeRot2_5);
		//myWorld.add_object(&cubeRot3);
		//myWorld.add_object(&cubeRot3_5);
		//myWorld.add_object(&cubeRot4);
		//myWorld.add_object(&cubeRot4_5);

		Cube cubeRot1(0.5f, 02.0f, 0.0f, 0.0f);
		Cube cubeRot2(0.5f, 05.0f, 0.0f, 0.0f);
		Cube cubeRot3(0.5f, 10.0f, 0.0f, 0.0f);
		Cube cubeRot4(0.5f, 15.0f, 0.0f, 0.0f);
		Cube cubeRot5(0.5f, 25.0f, 0.0f, 0.0f);
		Cube cubeRot6(0.5f, 30.0f, 0.0f, 0.0f);
		Cube cubeRot7(0.5f, 35.0f, 0.0f, 0.0f);
		Cube cubeRot8(0.5f, 40.0f, 0.0f, 0.0f);

		//Cube cubeRot1(0.5, 0, 02, 0);
		//Cube cubeRot2(0.5, 0, 05, 0);
		//Cube cubeRot3(0.5, 0, 10, 0);
		//Cube cubeRot4(0.5, 0, 15, 0);
		//Cube cubeRot5(0.5, 0, 25, 0);
		//Cube cubeRot6(0.5, 0, 30, 0);
		//Cube cubeRot7(0.5, 0, 35, 0);
		//Cube cubeRot8(0.5, 0, 40, 0);

		//Cube cubeRot1(0.5,  0,0, 02);
		//Cube cubeRot2(0.5, 0, 0, 05);
		//Cube cubeRot3(0.5, 0, 0, 10);
		//Cube cubeRot4(0.5, 0, 0, 15);
		//Cube cubeRot5(0.5, 0, 0, 25);
		//Cube cubeRot6(0.5, 0, 0, 30);
		//Cube cubeRot7(0.5, 0, 0, 35);
		//Cube cubeRot8(0.5, 0, 0, 40);

		myWorld.addObject(&cubeRot1);
		myWorld.addObject(&cubeRot2);
		myWorld.addObject(&cubeRot3);
		myWorld.addObject(&cubeRot4);
		myWorld.addObject(&cubeRot5);
		myWorld.addObject(&cubeRot6);
		myWorld.addObject(&cubeRot7);
		myWorld.addObject(&cubeRot8);
		//myWorld.worldMain();
		
		for(;;)
		{
			//myWorld.calculateCameraRotation();
			myWorld.handleAction();
			//myWorld.calculateWorldToCameraMatrix();
			//myWorld.worldMain();
			myWorld.render();
		}
		
		/*
		for(;;)
		{
			myWorld.update_mouse_pos();
			myWorld.handle_action();
			myWorld.render();
		}
		*/
	

	return 0;
}