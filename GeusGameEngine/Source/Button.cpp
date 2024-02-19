#pragma once

#include "Button.h"

Button::Button(Vector2Custom<int> dimensions, Vector2Custom<int> position, std::string label)
	: mDimensions(dimensions), mPosition(position), mLabel(label)
{
}

Button::~Button()
{
}

Vector2Custom<int> Button::transformToLocal(int worldX, int worldY)
{
	return Vector2Custom<int>(worldX - mPosition.mX, worldY - mPosition.mY);
}

bool Button::isInDimensions(Vector2Custom<int> point)
{
	if (point.mX < 0 || point.mY < 0)
	{
		return false;
	}

	return point.mX < mDimensions.mX && point.mY < mDimensions.mY;
}

bool Button::isClicked(int x, int y)
{
	auto loc = transformToLocal(x, y);
	
	return isInDimensions(loc);
}
