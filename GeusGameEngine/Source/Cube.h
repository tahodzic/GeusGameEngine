#pragma once

#include "IRenderable.h"
#include "IRenderer.h"
#include "Vector3.h"
#include "Matrix44.h"
#include "Transform.h"

#include <memory>

class Cube : public IRenderable
{
private:
	std::shared_ptr<IRenderer> mRenderer;
	Transform mTransform;

public:
	Cube(std::shared_ptr<IRenderer> renderer, const float s, const float x, const float y, const float z);

	~Cube();

	Vector3<float> mPosition;

	std::vector<Vector3<float>> mVertices;

	std::vector<Vector3<float>> mVerticesWorld;

	std::vector<int> mIndices;

	Matrix44<float> mLocalToWorldMatrix;

	void Render(const Matrix44<float>& worldToCameraMatrix)  override;

};