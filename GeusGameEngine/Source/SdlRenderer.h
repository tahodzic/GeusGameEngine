#pragma once

#include "IRenderer.h"
#include "Vector2Custom.h"
#include "Vector3Custom.h"
#include "Matrix44.h"
#include "Plane.h"

#include <SDL.h>
#include <memory>
#include <vector>

class SdlRenderer : public IRenderer
{
private:
    std::shared_ptr<SDL_Renderer> mpRenderer;

    static constexpr int sNrOfPlanes = 6;

    Plane mPlanes[sNrOfPlanes];

    const int& kWindowWidth;

    const int& kWindowHeight;

    const int& kCanvasWidth;

    const int& kCanvasHeight;

    const Matrix44<float>& kProjectionMatrix;

    bool computePixelCoordinates(
        const Vector3Custom<float>& worldPoint,
        const Matrix44<float>& worldToCameraMatrix,
        const Matrix44<float>& projectionMatrix,
        const int& imageWidth,
        const int& imageHeight,
        const int& canvasWidth,
        const int& canvasHeight,
        Vector2Custom<int>& rasterPoint);
    

    void clipToViewFrustum(
        const Vector3Custom<float>& vector1,
        const Vector3Custom<float>& vector2,
        Vector3Custom<float>& newV1,
        Vector3Custom<float>& newV2,
        const Matrix44<float>& worldToCameraMatrix
    );

    bool calculateLinePlaneIntersection(
        const Vector3Custom<float>& direction,
        const Vector3Custom<float>& p1,
        const Vector3Custom<float>& p2,
        const Plane& plane,
        Vector3Custom<float>& intersection);

    void CalculateTriangle(
        const Vector3Custom<float>& vector1,
        const Vector3Custom<float>& vector2,
        const Vector3Custom<float>& vector3,
        Vector2Custom<int>& vRaster1,
        Vector2Custom<int>& vRaster2,
        Vector2Custom<int>& vRaster3,
        const Matrix44<float>& worldToCameraMatrix);

public:
    SdlRenderer(std::shared_ptr<SDL_Renderer> renderer, const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight,
        const Matrix44<float>& projectionMatrix);

    ~SdlRenderer();

    int SetDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

    void RenderClear() override;

    void RenderPresent() override;

    void RenderPolygon(
        const std::vector<Vector3Custom<float>>& vertices,
        const std::vector<int>& indices,
        const Matrix44<float>& worldToCameraMatrix) override;

    void RenderDrawLine(
        const Vector3Custom<float>& vector1,
        const Vector3Custom<float>& vector2,
        const Matrix44<float>& worldToCameraMatrix) override;
    
    void RenderDrawRect(int height, int width, int x, int y) override;

    void extractAllPlanes();

    static std::shared_ptr<SdlRenderer> initialize(std::shared_ptr<SDL_Renderer> renderer, const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight,
        const Matrix44<float>& projectionMatrix);

    //void PollEvent(&mpSdlEvent) override;

    //void CreateTextureFromSurface(mRenderer, posSrfc) override;

    //void RenderCopy(mRenderer, posTexture, NULL, &textRect) override;

    //void FreeSurface(posSrfc) override;

    //void DestroyTexture(posTexture) override;

    //void RenderDrawRect(&rect) override;
};