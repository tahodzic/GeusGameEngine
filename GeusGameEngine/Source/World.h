#pragma once

#include <Windows.h>
#include <string>
#include <cmath>

#include <sstream>
#include <iomanip>  

#include "IMediaLayer.h"

#include "Cube.h"
#include "Camera.h"
#include "CoordinateSystemGrid.h"
#include "ViewPort.h"

#include <SDL.h>

#include "Matrix44.h"
#include "Vector3.h"
#include "Vector2.h"

#include "Button.h"


class World
{
private:

public:
    World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, Button button1, Button button2);

    ~World();
    
    static World CreateAndInitialize();

    Matrix44<float> mWtcMatrix;

    std::shared_ptr<IMediaLayer> mMediaLayer;

    Camera mCamera;

    CoordinateSystemGrid mCoordinateSystemGrid;

    ViewPort mViewPort;

    std::vector<Cube> mObjects;

    int mObjectCount;

    int mMousePrevX, mMousePrevY;

    int mMouseDiffX, mMouseDiffY;

    SDL_Event mSdlEvent;

    Button mButtonReset;

    Button mButtonCreate;

    static constexpr int sFontSize = 12;

    void HandleAction();

    void HandleKeyEvents();

    void ResetScene();

    bool PollKeyEvents();

    void Render();

    void AddObject(const Cube object);

    Cube CreateCube(const float s, const float x, const float y, const float z);

    void RenderButton();

    void RenderObjects();

    void RenderCoordinateSystem();

    void RenderViewPort();

    void CalculateWorldToCameraMatrix();

    void WorldMain();
};