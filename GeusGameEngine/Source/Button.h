#pragma once

#include <string>

#include "Vector2Custom.h"

class Button
{
private:
	
	Vector2Custom<int> transformToLocal(int worldX, int worldY);

	bool isInDimensions(Vector2Custom<int> point);

public:
	std::string mLabel;

	Vector2Custom<int> mDimensions;

	Vector2Custom<int> mPosition;
	
	Button(Vector2Custom<int> dimensions, Vector2Custom<int> position, std::string label);

	~Button();

	bool isClicked(int x, int y);
};

