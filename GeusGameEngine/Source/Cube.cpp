#pragma once
#include "Cube.h"

Cube::Cube()
{

}

/*
* Center-origin
* Right-Handed Coordinate System (z comes towards screen)
			   y

				│
				│
				│
				│
				│
				│
				└──────────────────────────────
			   /                               x
			  /
			 /        s                        half = s/2
			/     H─────────G  
		   /     /|        /│  M=(X,Y,Z)
		  /     / |       / │  A=(X-half,Y-half,Z+half)
		 /     E─────────F  │  B=(X+half,Y-half,Z+half)
		/      │  |      │  │  C=(X+half,Y-half,Z-half)
	   /       │  |  M   │  │  D=(X-half,Y-half,Z-half)
	  /        │  D------│--C  E=(X-half,Y+half,Z+half)
	 /         │ /       │ /   F=(X+half,Y+half,Z+half)
	/          │/        │/    G=(X+half,Y+half,Z-half)
   z           A─────────B	   H=(X-half,Y+half,Z-half)
*/

Cube::Cube(const float s, const float x, const float y, const float z)
{
	float half = s / 2.0f;

	// Define 8 unique vertices
	mVertices.push_back(Vector3Custom<float>(x - half, y - half, z + half));  // A = 0: 
	mVertices.push_back(Vector3Custom<float>(x + half, y - half, z + half));  // B = 1: 
	mVertices.push_back(Vector3Custom<float>(x + half, y - half, z - half));  // C = 2: 
	mVertices.push_back(Vector3Custom<float>(x - half, y - half, z - half));  // D = 3: 
	mVertices.push_back(Vector3Custom<float>(x - half, y + half, z + half));  // E = 4: 
	mVertices.push_back(Vector3Custom<float>(x + half, y + half, z + half));  // F = 5: 
	mVertices.push_back(Vector3Custom<float>(x + half, y + half, z - half));  // G = 6: 
	mVertices.push_back(Vector3Custom<float>(x - half, y + half, z - half));  // H = 7: 

	// Define triangles using indices
	// 6 faces, 12 triangles
	// bottom:	ABC, ACD (012, 023)
	// front:	ABF, AFE (015, 054)
	// left:	ADH, AHE (037, 074)
	// right:	BCG, BGF (126, 165)
	// back:	CDH, CHG (237, 276)
	// top:		EFG, EGH (456, 467)
	mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(2);
	mIndices.push_back(0); mIndices.push_back(2); mIndices.push_back(3);

	mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(5);
	mIndices.push_back(0); mIndices.push_back(5); mIndices.push_back(4);

	mIndices.push_back(0); mIndices.push_back(3); mIndices.push_back(7);
	mIndices.push_back(0); mIndices.push_back(7); mIndices.push_back(4);

	mIndices.push_back(1); mIndices.push_back(2); mIndices.push_back(6);
	mIndices.push_back(1); mIndices.push_back(6); mIndices.push_back(5);

	mIndices.push_back(2); mIndices.push_back(3); mIndices.push_back(7);
	mIndices.push_back(2); mIndices.push_back(7); mIndices.push_back(6);

	mIndices.push_back(4); mIndices.push_back(5); mIndices.push_back(6);
	mIndices.push_back(4); mIndices.push_back(6); mIndices.push_back(7);

}

Cube::~Cube()
{

}