#pragma once
#include <vector>

#include "Vector3Custom.h"

class Cube
{
private:



public:
	Cube();
	Cube(const float s, const float x, const float y, const float z);
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