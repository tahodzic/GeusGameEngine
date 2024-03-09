#pragma once

#include "IRenderer.h"
#include "Vector3Custom.h"
#include "Matrix44.h"

#include <memory>

class Cube
{
private:
	std::shared_ptr<IRenderer> mRenderer;

public:
	Cube(std::shared_ptr<IRenderer> renderer, const float s, const float x, const float y, const float z);

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

	void Render(const Matrix44<float>& worldToCameraMatrix);

	void LocalToWorld();

	void UpdateVertices();

	void Roll(const float change);

	void Pitch(const float change);

	void Yaw(const float change);

	void UpdateRollMatrix();

	void UpdatePitchMatrix();

	void UpdateYawMatrix();

	void CalculateRotations();
};