#pragma once
#include <vector>

#include "Vector3Custom.h"
#include "Matrix44.h"

class Cube
{
private:



public:
	Cube();
	Cube(const float s, const float x, const float y, const float z);
	~Cube();

	Vector3Custom<float> mPosition;

	std::vector<Vector3Custom<float>> mVertices;

	std::vector<Vector3Custom<float>> mVerticesWorld;

	std::vector<int> mIndices;

	Matrix44<float> mLocalToWorldMatrix;

	Matrix44<float> mRollMatrix;

	Matrix44<float> mPitchMatrix;

	Matrix44<float> mYawMatrix;

	Matrix44<float> mCombinedRotations;

	float mRoll;

	float mPitch;

	float mYaw;

	void Roll(const float change);

	void Pitch(const float change);

	void Yaw(const float change);

	void LocalToWorld();

	void UpdateRollMatrix();

	void UpdatePitchMatrix();

	void UpdateYawMatrix();

	void CalculateRotations();
	
	void UpdateVertices();
};