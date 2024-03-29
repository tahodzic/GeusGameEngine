#pragma once

#include <string>

#include "IRenderable.h"
#include "IRenderer.h"
#include "IFont.h"
#include "Matrix44.h"
#include "Vector2.h"

class Button : IRenderable
{
private:
	
	Vector2<int> TransformToLocal(int worldX, int worldY);

	bool IsInDimensions(Vector2<int> point);

public:
	Button(Vector2<int> dimensions, Vector2<int> position, std::string label, std::shared_ptr<IFont> fontHandler, std::shared_ptr<IRenderer> renderer);

	~Button();

	std::shared_ptr<IFont> mFontHandler;

	std::shared_ptr<IRenderer> mRenderer;

	std::string mLabel;

	Vector2<int> mDimensions;

	Vector2<int> mPosition;

	void Render(const Matrix44<float>& worldToCameraMatrix) override;

	bool IsClicked(int x, int y);
};

