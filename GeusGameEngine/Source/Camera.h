#pragma once

#include <cmath>

#include "Vector3Custom.h"
#include "Matrix44.h"

constexpr double kPi = 3.14159265358979323846;

class Camera
{
private:
    Matrix44<float> mProjectionMatrix;
public:
    Camera();

    Vector3Custom<float> mCamera = { 0.2f, 0.5f,1.3f };

    Matrix44<float> mWtcMatrix;

    const Matrix44<float>& kProjectionMatrixRef;

    Matrix44<float> mCombinedRotations;

    Matrix44<float> mRollMatrix;

    Matrix44<float> mPitchMatrix;

    Matrix44<float> mYawMatrix;

    float mRoll = 0;

    float mPitch = 0;

    float mYaw = 0;

    static constexpr float sAngleOfViewW = 90.0f * (static_cast<float>(kPi) / 180.0f);

    static constexpr float sAngleOfViewH = 120.0f * (static_cast<float>(kPi) / 180.0f);

    static constexpr float sZNear = 1.0f; 

    static constexpr float sZFar = 1000.0f; 

    static constexpr  float sCanvasW = 16.0f;

    static constexpr  float sCanvasH = 9.0f;

    static constexpr  float sAspectRatio = sCanvasW / sCanvasH;
    
    const float  sTop = sZNear * tan(sAngleOfViewW / 2.0f);

    const float  sBottom = -sTop;

    const float  sRight = sAspectRatio * sTop;

    const float  sLeft = -sRight;

    void updateRollMatrix();

    void updatePitchMatrix();

    void updateYawMatrix();
    
    void transformWorldToCamera(const Vector3Custom<float>& worldPoint, Vector3Custom<float>& cameraPoint);
    
    void updateWorldToCameraMatrix();

    void moveCamera(Vector3Custom<float>& translation);

    void calculateCameraRotation();
};

