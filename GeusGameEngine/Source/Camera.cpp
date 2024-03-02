#pragma once

#include "Camera.h"

Camera::Camera() : kProjectionMatrixRef(mProjectionMatrix), mCamera({ sDefaultX, sDefaultY, sDefaultZ}), mPitch(0.0f), mRoll(0.0f), mYaw(0.0f)
{
    mProjectionMatrix[0][0] = (2 * sZNear) / (sRight - sLeft);
    mProjectionMatrix[0][2] = (sRight + sLeft) / (sRight - sLeft);
    mProjectionMatrix[1][1] = (2 * sZNear) / (sTop - sBottom);
    mProjectionMatrix[1][2] = (sTop + sBottom) / (sTop - sBottom);
    mProjectionMatrix[2][2] = (sZFar + sZNear) / (sZFar - sZNear);
    mProjectionMatrix[2][3] = (2 * sZFar * sZNear) / (sZFar - sZNear);
    mProjectionMatrix[3][2] = -1.0f;
    mProjectionMatrix[3][3] = 0.0f;

	mRollMatrix =
	{
	    cos(mRoll), -sin(mRoll), 0, 0, 
	    sin(mRoll), cos(mRoll), 0, 0, 
	    0, 0, 1, 0, 
	    0, 0, 0, 1
	};

	mPitchMatrix =
	{
	    1, 0, 0, 0, 
	    0, cos(mPitch), -sin(mPitch), 0, 
	    0, sin(mPitch), cos(mPitch), 0, 
	    0, 0, 0, 1
	};

	mYawMatrix =
	{
	    cos(mYaw), 0, sin(mYaw), 0, 
	    0, 1, 0, 0, 
	    -sin(mYaw), 0, cos(mYaw), 0, 
	    0, 0, 0, 1
	};
}

void Camera::Reset()
{
    mCamera.mX = sDefaultX;
    mCamera.mY = sDefaultY;
    mCamera.mZ = sDefaultZ;
    mPitch = 0.0f;
    mYaw = 0.0f;
    mRoll = 0.0f;
    updatePitchMatrix();
    updateYawMatrix();
    updateRollMatrix();
}

void Camera::updateRollMatrix()
{
    mRollMatrix[0][0] = cos(mRoll);
    mRollMatrix[0][1] = -sin(mRoll);
    mRollMatrix[1][0] = sin(mRoll);
    mRollMatrix[1][1] = cos(mRoll);
};

void Camera::updatePitchMatrix()
{
    mPitchMatrix[1][1] = cos(mPitch);
    mPitchMatrix[1][2] = -sin(mPitch);
    mPitchMatrix[2][1] = sin(mPitch);
    mPitchMatrix[2][2] = cos(mPitch);
};

void Camera::updateYawMatrix()
{
    mYawMatrix[0][0] = cos(mYaw);
    mYawMatrix[0][2] = sin(mYaw);
    mYawMatrix[2][0] = -sin(mYaw);
    mYawMatrix[2][2] = cos(mYaw);
}

void Camera::transformWorldToCamera(const Vector3Custom<float>& worldPoint,  Vector3Custom<float>& cameraPoint)
{
    mWtcMatrix.multVecMatrix(worldPoint,  cameraPoint);
}

void Camera::UpdateWorldToCameraMatrix()
{
    // define camera translation
    Matrix44<float> translationMatrix = {
    1,  0,  0,  -mCamera.mX, 
    0,  1,  0,  -mCamera.mY, 
    0,  0,  1,  -mCamera.mZ, 
    0,  0,  0,  1
    };

    // invert pitch,  roll,  yaw
    auto invRot = mCombinedRotations.inverse();

    // World-To-Camera-Matrix 
    mWtcMatrix = invRot * translationMatrix;
 }


void Camera::moveCamera(Vector3Custom<float>& translation)
{
    Vector3Custom<float> xVec(mCombinedRotations[0][0],  mCombinedRotations[0][1],  mCombinedRotations[0][2]);
    Vector3Custom<float> yVec(mCombinedRotations[1][0],  mCombinedRotations[1][1],  mCombinedRotations[1][2]);
    Vector3Custom<float> zVec(mCombinedRotations[2][0],  mCombinedRotations[2][1],  mCombinedRotations[2][2]);
    auto xtr = xVec * translation.mX;
    auto ytr = yVec * translation.mY;
    auto ztr = zVec * translation.mZ;
    mCamera = mCamera + xtr;
    mCamera = mCamera + ytr;
    mCamera = mCamera + ztr;
}

void Camera::RollCamera(const float change)
{
    mRoll += change;
    mRoll = fmod(mRoll, 2.0f * static_cast<float>(Constants::pi));
    updateRollMatrix();
}

void Camera::PitchCamera(const float change)
{
    mPitch += change;
    mPitch = fmod(mPitch, 2.0f * static_cast<float>(Constants::pi));
    updatePitchMatrix();
}

void Camera::YawCamera(const float change)
{
    mYaw += change;
    mYaw = fmod(mYaw, 2.0f * static_cast<float>(Constants::pi));
    updateYawMatrix();
}

void Camera::calculateCameraRotation()
{
    // Order is Yaw -> Pitch -> Roll,  but C++
    mCombinedRotations = mRollMatrix * mPitchMatrix * mYawMatrix;
}



