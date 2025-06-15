#pragma once

#include "IMediaLayer.h"
#include "IRenderable.h"
#include "Vector2.h"
#include "Vector3.h"

#include <vector>

class CoordinateSystemGrid : IRenderable
{
private:
	CoordinateSystemGrid(const std::vector<Vector3<float>> xVectors, const std::shared_ptr<IMediaLayer> mediaLayer);

public:
	~CoordinateSystemGrid();

	static constexpr int sGridSize = 10;

	static constexpr int sGridFieldSize = 1;

	static constexpr float sGridLineLength = 10.0f;

	const std::shared_ptr<IMediaLayer> mMediaLayer;

	const std::vector<Vector3<float>> mGridVectors;
	
	const Vector3<float> mYStart;

	const Vector3<float> mYEnd;

	std::vector<Vector3<float>> mVertices;

	std::vector<int> mIndices;

	void Render(const Matrix44<float>& worldToCameraMatrix) override;

	static CoordinateSystemGrid CreateWithGrid(const std::shared_ptr<IMediaLayer> mediaLayer);

	static void CreateGrid(std::vector<Vector3<float>>& grid);
};