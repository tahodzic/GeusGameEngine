#pragma once

#include "CoordinateSystemGrid.h"

CoordinateSystemGrid::CoordinateSystemGrid(const std::vector<Vector3<float>> gridVectors, const std::shared_ptr<IMediaLayer> mediaLayer) :
    mMediaLayer(mediaLayer),
    mGridVectors(gridVectors),
    mYStart(0.0f, -sGridLineLength, 0.0f),
    mYEnd(0.0f, sGridLineLength, 0.0f)
{
}

CoordinateSystemGrid::~CoordinateSystemGrid()
{
}

CoordinateSystemGrid CoordinateSystemGrid::CreateWithGrid(std::shared_ptr<IMediaLayer> mediaLayer)
{
    std::vector<Vector3<float>> gridVectors;

    CreateGrid(gridVectors);

    return CoordinateSystemGrid(gridVectors, mediaLayer);
}

void CoordinateSystemGrid::CreateGrid(std::vector<Vector3<float>>& grid)
{
    float gridStart = static_cast<float>(sGridSize) * static_cast<float>(sGridFieldSize);
    float gridEnd = -gridStart;
    int count = sGridSize / sGridFieldSize;

    for (int i = 0; i <= count; i++)
    {
        float step = static_cast<float>(i);
        grid.emplace_back(gridStart, 0.0f, gridStart - (step * 2.0f));
        grid.emplace_back(gridEnd, 0.0f, gridStart - (step * 2.0f));

        grid.emplace_back(gridStart - (step * 2.0f), 0.0f, gridStart);
        grid.emplace_back(gridStart - (step * 2.0f), 0.0f, gridEnd);
    }
}

void CoordinateSystemGrid::Render(const Matrix44<float>& worldToCameraMatrix) 
{
    const bool inWorld = true;

    for (size_t i = 0; i < (mGridVectors.size() - 1); i += 2)
    {
        mMediaLayer->RenderLine(mGridVectors[i], mGridVectors[i+1], worldToCameraMatrix, inWorld);
    }

    mMediaLayer->RenderLine(mYStart, mYEnd, worldToCameraMatrix, inWorld);
}