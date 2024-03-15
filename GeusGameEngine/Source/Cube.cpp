#include "Cube.h"

#include "Constants.h"
#include "Transform.h"

Cube::Cube(std::shared_ptr<IRenderer> renderer, const float s, const float x, const float y, const float z) : 
	mRenderer(renderer), mPosition(x, y, z), mTransform()
{
	float half = s / 2.0f;

	// Define 8 unique vertices
	mVertices.push_back(Vector3Custom<float>(-half, -half, +half));  // A = 0: 
	mVertices.push_back(Vector3Custom<float>(+half, -half, +half));  // B = 1: 
	mVertices.push_back(Vector3Custom<float>(+half, -half, -half));  // C = 2: 
	mVertices.push_back(Vector3Custom<float>(-half, -half, -half));  // D = 3: 
	mVertices.push_back(Vector3Custom<float>(-half, +half, +half));  // E = 4: 
	mVertices.push_back(Vector3Custom<float>(+half, +half, +half));  // F = 5: 
	mVertices.push_back(Vector3Custom<float>(+half, +half, -half));  // G = 6: 
	mVertices.push_back(Vector3Custom<float>(-half, +half, -half));  // H = 7: 

	// Define triangles using indices
	// 6 faces, 12 triangles
	// bottom:	ABC, ACD (012, 023)
	// front:	ABF, AFE (015, 054)
	// left:	ADH, AHE (037, 074)
	// right:	BCG, BGF (126, 165)
	// back:	CDH, CHG (237, 276)
	// top:		EFG, EGH (456, 467)
	mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(2);
	mIndices.push_back(0); mIndices.push_back(2); mIndices.push_back(3);

	mIndices.push_back(0); mIndices.push_back(1); mIndices.push_back(5);
	mIndices.push_back(0); mIndices.push_back(5); mIndices.push_back(4);

	mIndices.push_back(0); mIndices.push_back(3); mIndices.push_back(7);
	mIndices.push_back(0); mIndices.push_back(7); mIndices.push_back(4);

	mIndices.push_back(1); mIndices.push_back(2); mIndices.push_back(6);
	mIndices.push_back(1); mIndices.push_back(6); mIndices.push_back(5);

	mIndices.push_back(2); mIndices.push_back(3); mIndices.push_back(7);
	mIndices.push_back(2); mIndices.push_back(7); mIndices.push_back(6);

	mIndices.push_back(4); mIndices.push_back(5); mIndices.push_back(6);
	mIndices.push_back(4); mIndices.push_back(6); mIndices.push_back(7);
}

Cube::~Cube()
{
}

void Cube::Render(const Matrix44<float>& worldToCameraMatrix)
{
	mTransform.CalculateRotations();
	
	mTransform.LocalToWorld(mPosition, mLocalToWorldMatrix);

	mRenderer->RenderPolygon(mVertices, mIndices, worldToCameraMatrix, mLocalToWorldMatrix, true);
}