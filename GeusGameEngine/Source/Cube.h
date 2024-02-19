#pragma once
#include <vector>

#include "Vector3Custom.h"

class Cube
{
private:



public:
	Cube();
	Cube(float s, float x, float y, float z);
	~Cube();

	// ########################################
	// Variables
	// ########################################

	std::vector<Vector3Custom<float>> mVertices; // List of unique vertices
	std::vector<int> mIndices;      // Index buffer for triangle lists

	// ########################################
	// Methods
	// ########################################
};