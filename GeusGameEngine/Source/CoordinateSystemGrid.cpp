#pragma once

#include "CoordinateSystemGrid.h"

CoordinateSystemGrid::CoordinateSystemGrid(float length, std::shared_ptr<IMediaLayer> mediaLayer) :
    mMediaLayer(mediaLayer),
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
    mMediaLayer->RenderLine(mXStart, mXEnd, worldToCameraMatrix, inWorld);
    mMediaLayer->RenderLine(mYStart, mYEnd, worldToCameraMatrix, inWorld);
    mMediaLayer->RenderLine(mZStart, mZEnd, worldToCameraMatrix, inWorld);
}