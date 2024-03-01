#pragma once

#include <cmath>

#include "Constants.h"
#include "Vector3Custom.h"
#include "Matrix44.h"


class Camera
{
private:
    Matrix44<float> mProjectionMatrix;

    static constexpr float sDefaultX = 0.2f;

    static constexpr float sDefaultY = 0.5f;

    static constexpr float sDefaultZ = 1.3f;

    static constexpr float sAngleOfViewW = 90.0f * (static_cast<float>(Constants::pi) / 180.0f);

    static constexpr float sAngleOfViewH = 120.0f * (static_cast<float>(Constants::pi) / 180.0f);

    static constexpr float sZNear = 1.0f;

    static constexpr float sZFar = 1000.0f;

    static constexpr  float sCanvasW = 16.0f;

    static constexpr  float sCanvasH = 9.0f;

    static constexpr  float sAspectRatio = sCanvasW / sCanvasH;

    const float  sTop = sZNear * tan(sAngleOfViewW / 2.0f);

    const float  sBottom = -sTop;

    const float  sRight = sAspectRatio * sTop;

    const float  sLeft = -sRight;

public:
    Camera();

    Vector3Custom<float> mCamera;

    Matrix44<float> mWtcMatrix;

    const Matrix44<float>& kProjectionMatrixRef;

    Matrix44<float> mCombinedRotations;

    Matrix44<float> mRollMatrix;

    Matrix44<float> mPitchMatrix;

    Matrix44<float> mYawMatrix;

    float mRoll;

    float mPitch;

    float mYaw;

    void reset();

    void updateRollMatrix();

    void updatePitchMatrix();

    void updateYawMatrix();
    
    void transformWorldToCamera(const Vector3Custom<float>& worldPoint, Vector3Custom<float>& cameraPoint);
    
    void updateWorldToCameraMatrix();

    void moveCamera(Vector3Custom<float>& translation);

    void calculateCameraRotation();
};

