#pragma once

#include "IMediaLayer.h"
#include "IRenderable.h"
#include "Vector2.h"

class ViewPort : IRenderable
{
private:
	std::shared_ptr<IMediaLayer> mMediaLayer;

public:
	ViewPort(std::shared_ptr<IMediaLayer> mediaLayer, const float x, const float y, const float w, const float h);

	const Vector2<float> mPosition;

	const Vector2<float> mDimensions;

	void Render(const Matrix44<float>& worldToCameraMatrix)  override;
};

