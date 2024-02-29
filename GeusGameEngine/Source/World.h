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
#include <SDL_ttf.h>

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

    Cube* mObjects[sMaxObjectsInWorld];

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

    TTF_Font* mFont;

    static constexpr int sFontSize = 12;

    void init();

    void handleAction();

    void handleKeyEvents();

    void resetScene();

    bool pollKeyEvents();

    void render();

    void addObject(Cube* object);

    Button mButtonReset;

    void renderButton();

    void UiDrawRectangle(Vector2Custom<int> dimensions, Vector2Custom<int> position, const bool inWorld);

    void renderObjects();

    void renderObject(const Cube& cube);

    void renderLine(const Vector3Custom<float>& vector1, const Vector3Custom<float>& vector2, const bool inWorld);

    void renderCoordinateSystem();

    void calculateWorldToCameraMatrix();

    void worldMain();
};