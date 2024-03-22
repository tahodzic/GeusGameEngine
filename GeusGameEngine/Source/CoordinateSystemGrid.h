#pragma once
#include <vector>

#include "Vector3.h"
#include "Vector2.h"

#include "IFont.h"
#include "IRenderable.h"
#include "IRenderer.h"

class CoordinateSystemGrid : IRenderable
{
private:

public:
	CoordinateSystemGrid(float length);
	CoordinateSystemGrid(float length, std::shared_ptr<IFont> fontHandler, std::shared_ptr<IRenderer> renderer);

	~CoordinateSystemGrid();
	std::shared_ptr<IFont> mFontHandler;
	std::shared_ptr<IRenderer> mRenderer;

	const Vector3<float> mXStart;

	const Vector3<float> mXEnd;

	const Vector3<float> mXText;

	const Vector3<float> mYStart;

	const Vector3<float> mYEnd;

	const Vector3<float> mYText;

	const Vector3<float> mZStart;

	const Vector3<float> mZEnd;

	const Vector3<float> mZText;

	std::vector<Vector3<float>> mVertices; // List of unique vertices

	std::vector<int> mIndices;      // Index buffer for triangle lists

	void drawUnitVector(int windowWidth, int windowHeight, const Vector2<int>& vec2D, Vector2<int>& out);

	void Render(const Matrix44<float>& worldToCameraMatrix) override;
};