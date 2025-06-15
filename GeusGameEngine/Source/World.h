#pragma once

#include "Camera.h"
#include "CoordinateSystemGrid.h"
#include "Cube.h"
#include "IInputObserver.h"
#include "IMediaLayer.h"
#include "InputTypes.h"
#include "Matrix44.h"
#include "Vector2.h"
#include "Vector3.h"
#include "ViewPort.h"

#include <cmath>
#include <iomanip>  
#include <sstream>
#include <string>
#include <Windows.h>


class World : public IInputObserver
{
private:

public:
    World(std::shared_ptr<IMediaLayer> mediaLayer, CoordinateSystemGrid coordinateSystemGrid, ViewPort viewPort);

    ~World();
    
    static std::shared_ptr<World> CreateAndInitialize(std::shared_ptr<IMediaLayer> mediaLayer);

    Matrix44<float> mWtcMatrix;

    std::shared_ptr<IMediaLayer> mMediaLayer;

    Camera mCamera;

    CoordinateSystemGrid mCoordinateSystemGrid;

    ViewPort mViewPort;

    std::vector<Cube> mObjects;

    int mObjectCount;

    InputTypes::InputState mInputState;

    static constexpr int sFontSize = 12;

    void HandleKeyDown(const InputTypes::InputEvent& event);

    void HandleMouseMotion(const InputTypes::InputEvent& inputEvent);

    void HandleMouseWheel(const InputTypes::InputEvent& inputEvent);

    void Render();

    void ResetScene();

    void AddObject(const Cube object);

    void CreateCube(const float s, const float x, const float y, const float z);

    void RenderObjects();

    void RenderCoordinateSystem();

    void RenderViewPort();

    void CalculateWorldToCameraMatrix();

    void Update(const InputTypes::InputEvent& event, [[maybe_unused]] const InputTypes::InputState& state) override;
};