#pragma once

#include "IRenderer.h"
#include "Vector2Custom.h"

class ViewPort
{
private:
	std::shared_ptr<IRenderer> mRenderer;

public:
	ViewPort(std::shared_ptr<IRenderer> renderer, const float x, const float y, const float w, const float h);

	const Vector2Custom<float> mPosition;

	const Vector2Custom<float> mDimensions;

	void Render(const Matrix44<float>& worldToCameraMatrix) const;
};

