#pragma once

#include "IRenderer.h"
#include "Vector2.h"
#include "Vector3.h"
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

    const Matrix44<float> mProjectionMatrix;

    const SDL_Rect mViewPort;

    void clipToViewFrustum(
        const Vector3<float>& vector1,
        const Vector3<float>& vector2,
        Vector3<float>& newV1,
        Vector3<float>& newV2,
        const Matrix44<float>& worldToCameraMatrix
    );

    bool calculateLinePlaneIntersection(
        const Vector3<float>& direction,
        const Vector3<float>& p1,
        const Vector3<float>& p2,
        const Plane& plane,
        Vector3<float>& intersection);

    void CalculateTriangle(
        const Vector3<float>& vector1,
        const Vector3<float>& vector2,
        const Vector3<float>& vector3,
        Vector2<int>& vRaster1,
        Vector2<int>& vRaster2,
        Vector2<int>& vRaster3,
        const Matrix44<float>& worldToCameraMatrix);



public:
    SdlRenderer(std::shared_ptr<SDL_Renderer> renderer, const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight,
       const Matrix44<float> projectionMatrix);

    ~SdlRenderer();

    int SetDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

    void SetRenderViewPort(const bool inWorld) override;

    void RenderClear() override;

    void RenderPresent() override;

    void RenderPolygon(
        const std::vector<Vector3<float>>& vertices,
        const std::vector<int>& indices,
        const Matrix44<float>& worldToCameraMatrix,
        const Matrix44<float>& localToWorldMatrix,
        const bool inWorld) override;

    void RenderDrawLine(
        const Vector3<float>& vector1,
        const Vector3<float>& vector2,
        const Matrix44<float>& worldToCameraMatrix,
        const bool inWorld) override;
    
    void RenderDrawRect(const int width, const int height, const int x, const int y, const bool inWorld) override;

    void ExtractAllPlanes();

    static std::shared_ptr<SdlRenderer> Initialize(std::shared_ptr<SDL_Renderer> renderer, const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight);

    //void PollEvent(&mpSdlEvent) override;

    //void CreateTextureFromSurface(mRenderer, posSrfc) override;

    //void RenderCopy(mRenderer, posTexture, NULL, &textRect) override;

    //void FreeSurface(posSrfc) override;

    //void DestroyTexture(posTexture) override;

    //void RenderDrawRect(&rect) override;
};