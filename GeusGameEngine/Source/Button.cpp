#pragma once

#include "Button.h"

Button::Button(Vector2<int> dimensions, Vector2<int> position, std::string label)
	: mDimensions(dimensions), mPosition(position), mLabel(label)
{
}

Button::~Button()
{
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