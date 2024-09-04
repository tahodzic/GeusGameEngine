#pragma once


#include "IMediaLayer.h"
#include "IRenderable.h"
#include "Matrix44.h"
#include "Vector2.h"

#include <string>
#include <functional>

class Button : IRenderable
{
private:
	
	Vector2<int> TransformToLocal(int worldX, int worldY);

	bool IsInDimensions(Vector2<int> point);

public:
	Button(Vector2<int> dimensions, Vector2<int> position, std::string label, std::function<void()> callback, std::shared_ptr<IMediaLayer> mediaLayer);

	~Button();

	std::shared_ptr<IMediaLayer> mMediaLayer;

	std::string mLabel;

	std::function<void()> mCallback;
	
	Vector2<int> mDimensions;

	Vector2<int> mPosition;

	void Render(const Matrix44<float>& worldToCameraMatrix) override;

	bool IsClicked(int x, int y);

	void OnClick();
};

