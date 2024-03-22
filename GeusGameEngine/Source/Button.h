#pragma once

#include <string>

#include "Vector2.h"

class Button
{
private:
	
	Vector2<int> TransformToLocal(int worldX, int worldY);

	bool IsInDimensions(Vector2<int> point);

public:
	std::string mLabel;

	Vector2<int> mDimensions;

	Vector2<int> mPosition;
	
	Button(Vector2<int> dimensions, Vector2<int> position, std::string label);

	~Button();

	bool IsClicked(int x, int y);
};

