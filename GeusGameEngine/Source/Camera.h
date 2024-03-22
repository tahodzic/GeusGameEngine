#pragma once

#include <cmath>

#include "Constants.h"
#include "Vector3.h"
#include "Matrix44.h"


class Camera
{
private:

    static constexpr float sDefaultX = 0.2f;

    static constexpr float sDefaultY = 0.5f;

    static constexpr float sDefaultZ = 1.3f;

public:
    Camera();

    Vector3<float> mPosition;

    Matrix44<float> mWtcMatrix;

    Matrix44<float> mCombinedRotations;

    Matrix44<float> mRollMatrix;

    Matrix44<float> mPitchMatrix;

    Matrix44<float> mYawMatrix;

    float mRoll;

    float mPitch;

    float mYaw;

    void Reset();

    void UpdateRollMatrix();

    void UpdatePitchMatrix();

    void UpdateYawMatrix();
    
    void TransformWorldToCamera(const Vector3<float>& worldPoint, Vector3<float>& cameraPoint);
    
    void UpdateWorldToCameraMatrix();

    void MoveCamera(Vector3<float>& translation);

    void RollCamera(const float change);
    
    void PitchCamera(const float change);
    
    void YawCamera(const float change);

    void CalculateCameraRotation();
};

