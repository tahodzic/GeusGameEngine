#pragma once

#include "CoordinateSystemGrid.h"

CoordinateSystemGrid::CoordinateSystemGrid(float length) :
    mXStart(-length, 0.0f, 0.0f),
    mXEnd(length, 0.0f, 0.0f),
    mXText(0.0f, 0.0f, 0.0f),
    mYStart(0.0f, -length, 0.0f),
    mYEnd(0.0f, length, 0.0f),
    mYText(0.0f, 0.0f, 0.0f),
    mZStart(0.0f, 0.0f, -length),
    mZEnd(0.0f, 0.0f, length),
    mZText(0.0f, 0.0f, 0.0f)
{

}

CoordinateSystemGrid::CoordinateSystemGrid(float length, std::shared_ptr<IFont> fontHandler, std::shared_ptr<IRenderer> renderer) :
    mFontHandler(fontHandler),
    mRenderer(renderer),
    mXStart(-length, 0.0f, 0.0f),
    mXEnd(length, 0.0f, 0.0f),
    mXText(0.0f, 0.0f, 0.0f),
    mYStart(0.0f, -length, 0.0f),
    mYEnd(0.0f, length, 0.0f),
    mYText(0.0f, 0.0f, 0.0f),
    mZStart(0.0f, 0.0f, -length),
    mZEnd(0.0f, 0.0f, length),
    mZText(0.0f, 0.0f, 0.0f)
{

}

CoordinateSystemGrid::~CoordinateSystemGrid()
{

}

void CoordinateSystemGrid::drawUnitVector(int windowWidth, int windowHeight, const Vector2<int>& vec2D, Vector2<int>& out)
{
    out.mX = windowWidth / 2 + vec2D.mX * 100;
    out.mY = windowHeight / 2 - vec2D.mY * 100;
}

void CoordinateSystemGrid::Render(const Matrix44<float>& worldToCameraMatrix) 
{
    const bool inWorld = true;
    mRenderer->RenderDrawLine(mXStart, mXEnd, worldToCameraMatrix, inWorld);
    mRenderer->RenderDrawLine(mYStart, mYEnd, worldToCameraMatrix, inWorld);
    mRenderer->RenderDrawLine(mZStart, mZEnd, worldToCameraMatrix, inWorld);
}