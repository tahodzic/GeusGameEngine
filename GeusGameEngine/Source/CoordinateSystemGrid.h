#pragma once
#include <vector>

#include "Vector3.h"
#include "Vector2.h"
#include "IMediaLayer.h"
#include "IRenderable.h"

class CoordinateSystemGrid : IRenderable
{
private:

public:
	CoordinateSystemGrid(float length, std::shared_ptr<IMediaLayer> mediaLayer);

	~CoordinateSystemGrid();

	std::shared_ptr<IMediaLayer> mMediaLayer;

	const Vector3<float> mXStart;

	const Vector3<float> mXEnd;

	const Vector3<float> mXText;

	const Vector3<float> mYStart;

	const Vector3<float> mYEnd;

	const Vector3<float> mYText;

	const Vector3<float> mZStart;

	const Vector3<float> mZEnd;

	const Vector3<float> mZText;

	std::vector<Vector3<float>> mVertices;

	std::vector<int> mIndices;

	void drawUnitVector(int windowWidth, int windowHeight, const Vector2<int>& vec2D, Vector2<int>& out);

	void Render(const Matrix44<float>& worldToCameraMatrix) override;
};