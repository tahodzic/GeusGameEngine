#include "ViewPort.h"

ViewPort::ViewPort(std::shared_ptr<IRenderer> renderer, const float x, const float y, const float w, const float h)
	: mRenderer(renderer), mPosition(x,y), mDimensions(w,h)
{
}

void ViewPort::Render(const Matrix44<float>& worldToCameraMatrix)
{
	mRenderer->RenderDrawRect(mDimensions.mX, mDimensions.mY, mPosition.mX, mPosition.mY,  false);
}
