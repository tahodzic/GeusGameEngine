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
#include "InputTypes.h"
#include "IInputObserver.h"

class World : public IInputObserver
{
private:

public:
    //World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort, UiManager uiManager);
    World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort);

    ~World();
    
    //static World CreateAndInitialize();
    static std::shared_ptr<World> CreateAndInitialize2(std::shared_ptr<IMediaLayer> mediaLayer);

    Matrix44<float> mWtcMatrix;

    std::shared_ptr<IMediaLayer> mMediaLayer;

    Camera mCamera;

    //InputManager mInputManager;

    //UiManager mUiManager;

    CoordinateSystemGrid mCoordinateSystemGrid;

    ViewPort mViewPort;

    std::vector<Cube> mObjects;

    int mObjectCount;

    InputTypes::InputState mInputState;

    static constexpr int sFontSize = 12;

    void HandleAction();

    void HandleKeyDown(const InputTypes::InputEvent& event);

    void HandleMouseButtonDown(const InputTypes::InputEvent& inputEvent);

    void HandleMouseMotion(const InputTypes::InputEvent& inputEvent);

    void HandleMouseWheel(const InputTypes::InputEvent& inputEvent);

    void HandleEvent(const InputTypes::InputEvent& event);

    void Render();

    void ResetScene();

    void AddObject(const Cube object);

    void CreateCube(const float s, const float x, const float y, const float z);

    //void RenderButton();

    void RenderObjects();

    void RenderCoordinateSystem();

    void RenderViewPort();

    void CalculateWorldToCameraMatrix();

    void WorldMain();

    void Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state) override;
};