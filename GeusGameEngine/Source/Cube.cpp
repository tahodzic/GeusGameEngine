#pragma once
#include "Cube.h"

#include "Constants.h"

Cube::Cube()
{

}

/*
* Center-origin
* Right-Handed Coordinate System (z comes towards screen)
			   y

				│
				│
				│
				│
				│
				│
				└──────────────────────────────
			   /                               x
			  /
			 /        s                        half = s/2
			/     H─────────G  
		   /     /|        /│  M=(X,Y,Z)
		  /     / |       / │  A=(X-half,Y-half,Z+half)
		 /     E─────────F  │  B=(X+half,Y-half,Z+half)
		/      │  |      │  │  C=(X+half,Y-half,Z-half)
	   /       │  |  M   │  │  D=(X-half,Y-half,Z-half)
	  /        │  D------│--C  E=(X-half,Y+half,Z+half)
	 /         │ /       │ /   F=(X+half,Y+half,Z+half)
	/          │/        │/    G=(X+half,Y+half,Z-half)
   z           A─────────B	   H=(X-half,Y+half,Z-half)
*/

Cube::Cube(const float s, const float x, const float y, const float z) : mPitch(0.0f), mRoll(0.0f), mYaw(0.0f), mPosition(x,y,z)
{
	float half = s / 2.0f;

	// Define 8 unique vertices
	//mVertices.push_back(Vector3Custom<float>(x - half, y - half, z + half));  // A = 0: 
	//mVertices.push_back(Vector3Custom<float>(x + half, y - half, z + half));  // B = 1: 
	//mVertices.push_back(Vector3Custom<float>(x + half, y - half, z - half));  // C = 2: 
	//mVertices.push_back(Vector3Custom<float>(x - half, y - half, z - half));  // D = 3: 
	//mVertices.push_back(Vector3Custom<float>(x - half, y + half, z + half));  // E = 4: 
	//mVertices.push_back(Vector3Custom<float>(x + half, y + half, z + half));  // F = 5: 
	//mVertices.push_back(Vector3Custom<float>(x + half, y + half, z - half));  // G = 6: 
	//mVertices.push_back(Vector3Custom<float>(x - half, y + half, z - half));  // H = 7: 
	mVertices.push_back(Vector3Custom<float>(- half, - half, + half));  // A = 0: 
	mVertices.push_back(Vector3Custom<float>(+ half, - half, + half));  // B = 1: 
	mVertices.push_back(Vector3Custom<float>(+ half, - half, - half));  // C = 2: 
	mVertices.push_back(Vector3Custom<float>(- half, - half, - half));  // D = 3: 
	mVertices.push_back(Vector3Custom<float>(- half, + half, + half));  // E = 4: 
	mVertices.push_back(Vector3Custom<float>(+ half, + half, + half));  // F = 5: 
	mVertices.push_back(Vector3Custom<float>(+ half, + half, - half));  // G = 6: 
	mVertices.push_back(Vector3Custom<float>(- half, + half, - half));  // H = 7: 

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

	UpdateRollMatrix();
	UpdatePitchMatrix();
	UpdateYawMatrix();
}

Cube::~Cube()
{

}

void Cube::LocalToWorld()
{
	// define camera translation
	Matrix44<float> translationMatrix = {
	1,  0,  0,  mPosition.mX,
	0,  1,  0,  mPosition.mY,
	0,  0,  1,  mPosition.mZ,
	0,  0,  0,  1
	};

	// invert pitch,  roll,  yaw
	auto invRot = mCombinedRotations.inverse();

	// World-To-Camera-Matrix 
	mLocalToWorldMatrix = translationMatrix * invRot;


	//UpdateVertices();
}

void Cube::UpdateRollMatrix()
{
	mRollMatrix[0][0] = cos(mRoll);
	mRollMatrix[0][1] = -sin(mRoll);
	mRollMatrix[1][0] = sin(mRoll);
	mRollMatrix[1][1] = cos(mRoll);
};

void Cube::UpdatePitchMatrix()
{
	mPitchMatrix[1][1] = cos(mPitch);
	mPitchMatrix[1][2] = -sin(mPitch);
	mPitchMatrix[2][1] = sin(mPitch);
	mPitchMatrix[2][2] = cos(mPitch);
};

void Cube::UpdateYawMatrix()
{
	mYawMatrix[0][0] = cos(mYaw);
	mYawMatrix[0][2] = sin(mYaw);
	mYawMatrix[2][0] = -sin(mYaw);
	mYawMatrix[2][2] = cos(mYaw);
}

void Cube::Roll(const float change)
{
	mRoll += change;
	mRoll = fmod(mRoll, 2.0f * static_cast<float>(Constants::pi));
	UpdateRollMatrix();
}

void Cube::Pitch(const float change)
{
	mPitch += change;
	mPitch = fmod(mPitch, 2.0f * static_cast<float>(Constants::pi));
	UpdatePitchMatrix();
}

void Cube::Yaw(const float change)
{
	mYaw += change;
	mYaw = fmod(mYaw, 2.0f * static_cast<float>(Constants::pi));
	UpdateYawMatrix();
}

void Cube::CalculateRotations()
{
    // Order is Yaw -> Pitch -> Roll,  but C++
    mCombinedRotations = mRollMatrix * mPitchMatrix * mYawMatrix;
}

void Cube::UpdateVertices()
{
	for (auto& vert : mVertices)
	{
		Vector3Custom<float> dst;
		mLocalToWorldMatrix.multVecMatrix(vert, dst);
		vert = dst;
	}
}