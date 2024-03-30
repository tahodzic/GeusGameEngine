#pragma once
#include "ViewPort.h"

ViewPort::ViewPort(std::shared_ptr<IMediaLayer> mediaLayer, const float x, const float y, const float w, const float h)
	: mMediaLayer(mediaLayer), mPosition(x,y), mDimensions(w,h)
{
}

void ViewPort::Render(const Matrix44<float>& worldToCameraMatrix)
{
	mMediaLayer->RenderRect(mDimensions.mX, mDimensions.mY, mPosition.mX, mPosition.mY,  false);
}
