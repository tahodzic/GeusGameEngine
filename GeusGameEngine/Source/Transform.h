#pragma once

#include "ITransform.h"

#include "Matrix44.h"
#include "Vector3Custom.h"

class Transform //: public ITransform
{
private:
	Matrix44<float> mLocalToWorldMatrix;

	Matrix44<float> mRollMatrix;

	Matrix44<float> mPitchMatrix;

	Matrix44<float> mYawMatrix;

	Matrix44<float> mCombinedRotations;

	float mRoll;

	float mPitch;

	float mYaw;

	

public:
	Transform();

	void Roll(const float change);

	void Pitch(const float change);

	void Yaw(const float change);

	void UpdateRollMatrix();

	void UpdatePitchMatrix();

	void UpdateYawMatrix();

	void CalculateRotations();

	void LocalToWorld(const Vector3Custom<float>& position, Matrix44<float>& localToWorldMatrix);
};