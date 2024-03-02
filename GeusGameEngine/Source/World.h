#pragma once

#include <Windows.h>
#include <string>
#include <cmath>

#include <sstream>      // std::stringstream
#include <iomanip>  

#include "MediaLayer.h"

#include "Cube.h"
#include "Camera.h"
#include "CoordinateSystemGrid.h"

#include <SDL.h>

#include "Matrix44.h"
#include "Vector3Custom.h"
#include "Vector2Custom.h"

#include "Button.h"


class World
{
private:

public:
    World();

    ~World();
    
    Matrix44<float> mWtcMatrix;

    Camera mCamera;

    CoordinateSystemGrid mCoordinateSystemGrid;

    static constexpr int sMaxObjectsInWorld = 10;

    std::vector<Cube> mObjects;

    int mObjectCount;

    SDL_Renderer* mRenderer;
    
    static constexpr std::string_view sTitle = "My Gamestudio";

    static constexpr int sWindowPosX = 20;

    static constexpr int sWindowPosY = 100;

    static constexpr int sWindowWidth = 1280;

    static constexpr int sWindowHeight = 720;

    static constexpr int sCanvasWidth = 2;

    static constexpr int sCanvasHeight = 2;

    int mMousePrevX = 0, mMousePrevY = 0;

    int mMouseDiffX, mMouseDiffY;

    Uint32 mMouseState;

    SDL_Event mpSdlEvent;

    Button mButtonReset;

    Button mButtonCreate;

    static constexpr int sFontSize = 12;

    void Initialize();

    void HandleAction();

    void HandleKeyEvents();

    void ResetScene();

    bool PollKeyEvents();

    void Render();

    void AddObject(const Cube object);

    Cube CreateCube(const float s, const float x, const float y, const float z);

    void RenderButton();

    void UiDrawRectangle(Vector2Custom<int> dimensions, Vector2Custom<int> position, const bool inWorld);

    void RenderObjects();

    void RenderObject(const Cube& cube);

    void RenderLine(const Vector3Custom<float>& vector1, const Vector3Custom<float>& vector2, const bool inWorld);

    void RenderCoordinateSystem();

    void CalculateWorldToCameraMatrix();

    void WorldMain();
};