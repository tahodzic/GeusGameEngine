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
#include "Matrix44.h"
#include "Vector3.h"
#include "Vector2.h"
#include "InputManager.h"
#include "UiManager.h"

class World
{
private:

public:
    World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, UiManager uiManager);

    ~World();
    
    static World CreateAndInitialize();

    Matrix44<float> mWtcMatrix;

    std::shared_ptr<IMediaLayer> mMediaLayer;

    Camera mCamera;

    InputManager mInputManager;

    UiManager mUiManager;

    CoordinateSystemGrid mCoordinateSystemGrid;

    ViewPort mViewPort;

    std::vector<Cube> mObjects;

    int mObjectCount;

    static constexpr int sFontSize = 12;

    void HandleAction();

    void HandleKeyDown(const InputManager::InputEvent& inputEvent);

    void HandleMouseButtonDown(const InputManager::InputEvent& inputEvent);

    void HandleMouseMotion(const InputManager::InputEvent& inputEvent);

    void HandleMouseWheel(const InputManager::InputEvent& inputEvent);

    void HandleKeyEvents();

    void Render();

    void ResetScene();

    void AddObject(const Cube object);

    Cube CreateCube(const float s, const float x, const float y, const float z);

    void RenderButton();

    void RenderObjects();

    void RenderCoordinateSystem();

    void RenderViewPort();

    void CalculateWorldToCameraMatrix();

    void WorldMain();
};