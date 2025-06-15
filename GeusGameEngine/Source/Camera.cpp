#include "Camera.h"

Camera::Camera() : mPosition({ sDefaultX, sDefaultY, sDefaultZ}), mPitch(0.0f), mRoll(0.0f), mYaw(0.0f)
{

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
    mPosition.mX = sDefaultX;
    mPosition.mY = sDefaultY;
    mPosition.mZ = sDefaultZ;
    mPitch = 0.0f;
    mYaw = 0.0f;
    mRoll = 0.0f;
    UpdatePitchMatrix();
    UpdateYawMatrix();
    UpdateRollMatrix();
}

void Camera::UpdateRollMatrix()
{
    mRollMatrix[0][0] = cos(mRoll);
    mRollMatrix[0][1] = -sin(mRoll);
    mRollMatrix[1][0] = sin(mRoll);
    mRollMatrix[1][1] = cos(mRoll);
};

void Camera::UpdatePitchMatrix()
{
    mPitchMatrix[1][1] = cos(mPitch);
    mPitchMatrix[1][2] = -sin(mPitch);
    mPitchMatrix[2][1] = sin(mPitch);
    mPitchMatrix[2][2] = cos(mPitch);
};

void Camera::UpdateYawMatrix()
{
    mYawMatrix[0][0] = cos(mYaw);
    mYawMatrix[0][2] = sin(mYaw);
    mYawMatrix[2][0] = -sin(mYaw);
    mYawMatrix[2][2] = cos(mYaw);
}

void Camera::TransformWorldToCamera(const Vector3<float>& worldPoint,  Vector3<float>& cameraPoint)
{
    mWtcMatrix.multVecMatrix(worldPoint,  cameraPoint);
}

void Camera::UpdateWorldToCameraMatrix()
{
    // define camera translation
    Matrix44<float> translationMatrix = {
    1,  0,  0,  -mPosition.mX, 
    0,  1,  0,  -mPosition.mY, 
    0,  0,  1,  -mPosition.mZ, 
    0,  0,  0,  1
    };

    // invert pitch,  roll,  yaw
    auto invRot = mCombinedRotations.inverse();

    // World-To-Camera-Matrix 
    mWtcMatrix = invRot * translationMatrix;
 }


void Camera::MoveCamera(Vector3<float>& translation)
{
    Vector3<float> xVec(mCombinedRotations[0][0],  mCombinedRotations[0][1],  mCombinedRotations[0][2]);
    Vector3<float> yVec(mCombinedRotations[1][0],  mCombinedRotations[1][1],  mCombinedRotations[1][2]);
    Vector3<float> zVec(mCombinedRotations[2][0],  mCombinedRotations[2][1],  mCombinedRotations[2][2]);

    Vector3<float> newTranslation;
    mCombinedRotations.multDirMatrix(translation, newTranslation);

    //mPosition.mX += (mCombinedRotations[0][0] * newTranslation.mX);
    //mPosition.mY += (mCombinedRotations[0][1] * newTranslation.mX);
    //mPosition.mZ += (mCombinedRotations[0][2] * newTranslation.mX);

    //mPosition.mX += (mCombinedRotations[1][0] * newTranslation.mY);
    //mPosition.mY += (mCombinedRotations[1][1] * newTranslation.mY);
    //mPosition.mZ += (mCombinedRotations[1][2] * newTranslation.mY);

    //mPosition.mX += (mCombinedRotations[2][0] * newTranslation.mZ);
    //mPosition.mY += (mCombinedRotations[2][1] * newTranslation.mZ);
    //mPosition.mZ += (mCombinedRotations[2][2] * newTranslation.mZ);

    auto xtr = xVec * newTranslation.mX;
    auto ytr = yVec * newTranslation.mY;
    auto ztr = zVec * newTranslation.mZ;
    mPosition = mPosition + xtr;
    mPosition = mPosition + ytr;
    mPosition = mPosition + ztr;
}

void Camera::RollCamera(const float change)
{
    mRoll += change;
    mRoll = fmod(mRoll, 2.0f * static_cast<float>(Constants::pi));
    UpdateRollMatrix();
}

void Camera::PitchCamera(const float change)
{
    mPitch += change;
    mPitch = fmod(mPitch, 2.0f * static_cast<float>(Constants::pi));
    UpdatePitchMatrix();
}

void Camera::YawCamera(const float change)
{
    mYaw += change;
    mYaw = fmod(mYaw, 2.0f * static_cast<float>(Constants::pi));
    UpdateYawMatrix();
}

void Camera::CalculateCameraRotation()
{
    // Order is Yaw -> Pitch -> Roll,  but C++
    mCombinedRotations = mRollMatrix * mPitchMatrix * mYawMatrix;
}