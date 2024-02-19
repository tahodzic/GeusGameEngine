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

CoordinateSystemGrid::~CoordinateSystemGrid()
{

}

void CoordinateSystemGrid::drawUnitVector(int windowWidth, int windowHeight, const Vector2Custom<int>& vec2D, Vector2Custom<int>& out)
{
    out.mX = windowWidth / 2 + vec2D.mX * 100;
    out.mY = windowHeight / 2 - vec2D.mY * 100;
}