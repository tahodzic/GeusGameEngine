#pragma once

#include <string>

#include "Vector2Custom.h"

class Button
{
private:
	
	Vector2Custom<int> TransformToLocal(int worldX, int worldY);

	bool IsInDimensions(Vector2Custom<int> point);

public:
	std::string mLabel;

	Vector2Custom<int> mDimensions;

	Vector2Custom<int> mPosition;
	
	Button(Vector2Custom<int> dimensions, Vector2Custom<int> position, std::string label);

	~Button();

	bool IsClicked(int x, int y);
};

