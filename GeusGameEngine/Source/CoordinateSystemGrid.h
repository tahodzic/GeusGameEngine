#pragma once
#include <vector>

#include "Vector3Custom.h"
#include "Vector2Custom.h"
class CoordinateSystemGrid
{
public:
	CoordinateSystemGrid(float length);
	~CoordinateSystemGrid();

	const Vector3Custom<float> mXStart;

	const Vector3Custom<float> mXEnd;

	const Vector3Custom<float> mXText;

	const Vector3Custom<float> mYStart;

	const Vector3Custom<float> mYEnd;

	const Vector3Custom<float> mYText;

	const Vector3Custom<float> mZStart;

	const Vector3Custom<float> mZEnd;

	const Vector3Custom<float> mZText;

	std::vector<Vector3Custom<float>> mVertices; // List of unique vertices

	std::vector<int> mIndices;      // Index buffer for triangle lists

	void drawUnitVector(int windowWidth, int windowHeight, const Vector2Custom<int>& vec2D, Vector2Custom<int>& out);
};