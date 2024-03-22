#include "Transform.h"

#include "Constants.h"

#include <cmath>

Transform::Transform()
{
}

void Transform::UpdateRollMatrix()
{
	mRollMatrix[0][0] = cos(mRoll);
	mRollMatrix[0][1] = -sin(mRoll);
	mRollMatrix[1][0] = sin(mRoll);
	mRollMatrix[1][1] = cos(mRoll);
}

void Transform::UpdatePitchMatrix()
{
	mPitchMatrix[1][1] = cos(mPitch);
	mPitchMatrix[1][2] = -sin(mPitch);
	mPitchMatrix[2][1] = sin(mPitch);
	mPitchMatrix[2][2] = cos(mPitch);
}

void Transform::UpdateYawMatrix()
{
	mYawMatrix[0][0] = cos(mYaw);
	mYawMatrix[0][2] = sin(mYaw);
	mYawMatrix[2][0] = -sin(mYaw);
	mYawMatrix[2][2] = cos(mYaw);
}


void Transform::Roll(const float change)
{
	mRoll += change;
	mRoll = fmod(mRoll, 2.0f * static_cast<float>(Constants::pi));
	UpdateRollMatrix();
}

void Transform::Pitch(const float change)
{
	mPitch += change;
	mPitch = fmod(mPitch, 2.0f * static_cast<float>(Constants::pi));
	UpdatePitchMatrix();
}

void Transform::Yaw(const float change)
{
	mYaw += change;
	mYaw = fmod(mYaw, 2.0f * static_cast<float>(Constants::pi));
	UpdateYawMatrix();
}

void Transform::CalculateRotations()
{
	// Order is Yaw -> Pitch -> Roll,  but C++
	mCombinedRotations = mRollMatrix * mPitchMatrix * mYawMatrix;
}

void Transform::LocalToWorld(const Vector3<float>& position, Matrix44<float>& localToWorldMatrix)
{
	// define camera translation
	Matrix44<float> translationMatrix = {
	1,  0,  0,  position.mX,
	0,  1,  0,  position.mY,
	0,  0,  1,  position.mZ,
	0,  0,  0,  1
	};

	// invert pitch,  roll,  yaw
	auto invRot = mCombinedRotations.inverse();

	// World-To-Camera-Matrix 
	localToWorldMatrix = translationMatrix * invRot;

	//UpdateVertices();
}