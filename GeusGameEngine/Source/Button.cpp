#pragma once

#include "Button.h"
#include "TextRenderer.h"

Button::Button(Vector2<int> dimensions, Vector2<int> position, std::string label, std::shared_ptr<IMediaLayer> mediaLayer)
	: mDimensions(dimensions), mPosition(position), mLabel(label), mMediaLayer(mediaLayer)
{
}

Button::~Button()
{
}

void Button::Render(const Matrix44<float>& worldToCameraMatrix)
{
	bool inWorld = false;

	TextRenderer::print(mLabel, mDimensions.mX + mPosition.mX, mDimensions.mY + mPosition.mY, inWorld);

	mMediaLayer->RenderRect(mDimensions.mX, mDimensions.mY, mPosition.mX, mPosition.mY, inWorld);
}

Vector2<int> Button::TransformToLocal(int worldX, int worldY)
{
	return Vector2<int>(worldX - mPosition.mX, worldY - mPosition.mY);
}

bool Button::IsInDimensions(Vector2<int> point)
{
	if (point.mX < 0 || point.mY < 0)
	{
		return false;
	}

	return point.mX < mDimensions.mX && point.mY < mDimensions.mY;
}

bool Button::IsClicked(int x, int y)
{
	auto loc = TransformToLocal(x, y);
	
	return IsInDimensions(loc);
}