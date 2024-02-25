#pragma once

#include "Vector2Custom.h"
#include "Vector3Custom.h"
#include "Matrix44.h"

#include <vector>

class IRenderer
{
public:

    virtual ~IRenderer() {}

    virtual int SetDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;

    virtual void RenderClear() = 0;

    virtual void RenderPresent() = 0;

    virtual void RenderDrawLine(
		const Vector3Custom<float>& vector1,
		const Vector3Custom<float>& vector2,
		const Matrix44<float>& worldToCameraMatrix) = 0;
	
	virtual void RenderPolygon(
		const std::vector<Vector3Custom<float>>& vertices,
		const std::vector<int>& indices,
		const Matrix44<float>& worldToCameraMatrix) = 0;

    virtual void RenderDrawRect(int width, int height, int x, int y) = 0;
};