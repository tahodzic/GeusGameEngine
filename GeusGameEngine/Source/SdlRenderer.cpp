#pragma once

#include "SdlRenderer.h"
#include "TextRenderer.h"

#include <SDL.h>

#include <sstream>      // std::stringstream
#include <iomanip>  
#include <windows.h>

SdlRenderer::SdlRenderer(
	std::shared_ptr<SDL_Renderer> renderer,
	 const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight, const Matrix44<float>& projectionMatrix) :
		mpRenderer(renderer),
		kWindowWidth(windowWidth),
		kWindowHeight(windowHeight),
		kCanvasWidth(canvasWidth),
		kCanvasHeight(canvasHeight),
		kProjectionMatrix(projectionMatrix),
		kViewPort{ 100,100,640,480 }
{
}

SdlRenderer::~SdlRenderer()
{
}

bool SdlRenderer::calculateLinePlaneIntersection(
	const Vector3Custom<float>& direction,
	const Vector3Custom<float>& p1,
	const Vector3Custom<float>& p2,
	const Plane &plane,
	Vector3Custom<float>& intersection)
{
	auto dividend = plane.mA * p1.mX + plane.mB * p1.mY + plane.mC * p1.mZ + plane.mD;

	auto divisor = plane.mA * direction.mX + plane.mB * direction.mY + plane.mC * direction.mZ;

	if (divisor == 0)
		return false;

	auto t = (-dividend) / divisor;

	if (t >= 0 && t <= 1)
	{
		intersection.mX = p1.mX + t * direction.mX;
		intersection.mY = p1.mY + t * direction.mY;
		intersection.mZ = p1.mZ + t * direction.mZ;
		return true;
	}

	return false;
}

int SdlRenderer::SetDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    return SDL_SetRenderDrawColor(mpRenderer.get(), r, g, b, a);
}

void SdlRenderer::RenderClear()
{
    SDL_RenderClear(mpRenderer.get());
}

void SdlRenderer::RenderPresent()
{
    SDL_RenderPresent(mpRenderer.get());
}

void SdlRenderer::clipToViewFrustum(
	const Vector3Custom<float>& worldVector1,
	const Vector3Custom<float>& worldVector2, 
	Vector3Custom<float>& outCameraVector1,
	Vector3Custom<float>& outCameraVector2,
	const Matrix44<float>& worldToCameraMatrix)
{
	Vector3Custom<float> cameraV1;
	worldToCameraMatrix.multVecMatrix(worldVector1, cameraV1);

	Vector3Custom<float> cameraV2;
	worldToCameraMatrix.multVecMatrix(worldVector2, cameraV2);

	auto direction = cameraV2 - cameraV1;

	for (int i = 0; i < sNrOfPlanes; i++)
	{
		Plane& plane = mPlanes[i];

		auto isP1 = plane.isPointInFront(cameraV1);
		auto isP2 = plane.isPointInFront(cameraV2);

		if (isP1 && isP2)
		{
			outCameraVector1 = cameraV1;
			outCameraVector2 = cameraV2;
		}
		else if (!isP1 && isP2)
		{
			calculateLinePlaneIntersection(direction, cameraV1, cameraV2, plane, outCameraVector1);
			cameraV1 = outCameraVector1;
		}
		else if (isP1 && !isP2)
		{
			calculateLinePlaneIntersection(direction, cameraV1, cameraV2, plane, outCameraVector2);
			cameraV2 = outCameraVector2;
		}
	}

	outCameraVector1 = cameraV1;
	outCameraVector2 = cameraV2;
}

void SdlRenderer::CalculateTriangle(
	const Vector3Custom<float>& vector1,
	const Vector3Custom<float>& vector2,
	const Vector3Custom<float>& vector3,
	Vector2Custom<int>& vRaster1,
	Vector2Custom<int>& vRaster2,
	Vector2Custom<int>& vRaster3,
	const Matrix44<float>& worldToCameraMatrix)
{
	Vector3Custom<float> cameraPoint1, cameraPoint2, cameraPoint3;
	clipToViewFrustum(
		vector1, vector2,
		cameraPoint1, cameraPoint2,
		worldToCameraMatrix
	);
	clipToViewFrustum(
		vector2, vector3,
		cameraPoint2, cameraPoint3,
		worldToCameraMatrix
	);
	clipToViewFrustum(
		vector3, vector1,
		cameraPoint3, cameraPoint1,
		worldToCameraMatrix
	);

	Vector3Custom<float> clipPoint1, clipPoint2, clipPoint3;
	kProjectionMatrix.multVecMatrix(cameraPoint1, clipPoint1);
	kProjectionMatrix.multVecMatrix(cameraPoint2, clipPoint2);
	kProjectionMatrix.multVecMatrix(cameraPoint3, clipPoint3);


	vRaster1.mX = static_cast<int>(std::floor((clipPoint1.mX * 0.5f + 0.5f) * kWindowWidth));
	vRaster1.mY = static_cast<int>(std::floor((1.0f - (clipPoint1.mY * 0.5f + 0.5f)) * kWindowHeight));

	vRaster2.mX = static_cast<int>(std::floor((clipPoint2.mX * 0.5f + 0.5f) * kWindowWidth));
	vRaster2.mY = static_cast<int>(std::floor((1.0f - (clipPoint2.mY * 0.5f + 0.5f)) * kWindowHeight));

	vRaster3.mX = static_cast<int>(std::floor((clipPoint3.mX * 0.5f + 0.5f) * kWindowWidth));
	vRaster3.mY = static_cast<int>(std::floor((1.0f - (clipPoint3.mY * 0.5f + 0.5f)) * kWindowHeight));



	/*int imageWidth = 320;
	int imageHeight = 240;
	vRaster1.mX = static_cast<int>(std::floor((clipPoint1.mX * 0.5f + 0.5f) * imageWidth));
	vRaster1.mY = static_cast<int>(std::floor((1.0f - (clipPoint1.mY * 0.5f + 0.5f)) * imageHeight));

	vRaster2.mX = static_cast<int>(std::floor((clipPoint2.mX * 0.5f + 0.5f) * imageWidth));
	vRaster2.mY = static_cast<int>(std::floor((1.0f - (clipPoint2.mY * 0.5f + 0.5f)) * imageHeight));

	vRaster3.mX = static_cast<int>(std::floor((clipPoint3.mX * 0.5f + 0.5f) * imageWidth));
	vRaster3.mY = static_cast<int>(std::floor((1.0f - (clipPoint3.mY * 0.5f + 0.5f)) * imageHeight));*/
}

void SdlRenderer:: RenderPolygon(
	const std::vector<Vector3Custom<float>>& vertices,
	const std::vector<int>& indices,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld)
{
	std::vector<SDL_Vertex> verticesToRender;

	SDL_Color col{ 255, 255, 255, 255};

	for (int i = 0; i < indices.size() / 3; i++)
	{
		const Vector3Custom<float>& v0World = vertices[indices[i * 3]];
		const Vector3Custom<float>& v1World = vertices[indices[i * 3 + 1]];
		const Vector3Custom<float>& v2World = vertices[indices[i * 3 + 2]];
		
		Vector2Custom<int> vRaster1, vRaster2, vRaster3;

		CalculateTriangle(v0World, v1World, v2World, vRaster1, vRaster2, vRaster3, worldToCameraMatrix);

		//vRaster1.mX += 100;
		//vRaster1.mY += 100;
		//vRaster2.mX += 100;
		//vRaster2.mY += 100;
		verticesToRender.push_back(SDL_Vertex{ {static_cast<float>(vRaster1.mX), static_cast<float>(vRaster1.mY)}, col, { 0, 0 } });
		verticesToRender.push_back(SDL_Vertex{ {static_cast<float>(vRaster2.mX), static_cast<float>(vRaster2.mY)}, col, { 0, 0 } });
		verticesToRender.push_back(SDL_Vertex{ {static_cast<float>(vRaster3.mX), static_cast<float>(vRaster3.mY)}, col, { 0, 0 } });
	}

	auto vertsSize = verticesToRender.size();
	constexpr int intMax = (std::numeric_limits<int>::max)();
	if (vertsSize > static_cast<size_t>(intMax))
	{
		throw std::overflow_error("size_t value is too big to fit into an int.");
	}

	SetRenderViewPort(inWorld);
	SDL_RenderGeometry(mpRenderer.get(), NULL, verticesToRender.data(), static_cast<int>(verticesToRender.size()), NULL, 0);
}

void SdlRenderer::RenderDrawLine(
	const Vector3Custom<float>& vector1,
	const Vector3Custom<float>& vector2,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld)
{
	// TODO: Consistent naming between vector and point
	Vector3Custom<float> cameraPoint1;
	Vector3Custom<float> cameraPoint2;
	clipToViewFrustum(
		vector1,
		vector2,
		cameraPoint1,
		cameraPoint2,
		worldToCameraMatrix
	);

	Vector3Custom<float> clipPoint1;
	Vector3Custom<float> clipPoint2;
	kProjectionMatrix.multVecMatrix(cameraPoint1, clipPoint1);
	kProjectionMatrix.multVecMatrix(cameraPoint2, clipPoint2);

	Vector2Custom<int> vRaster1, vRaster2;
	vRaster1.mX = static_cast<int>(std::floor((clipPoint1.mX * 0.5f + 0.5f) * kWindowWidth));
	vRaster1.mY = static_cast<int>(std::floor((1.0f - (clipPoint1.mY * 0.5f + 0.5f)) * kWindowHeight));

	vRaster2.mX = static_cast<int>(std::floor((clipPoint2.mX * 0.5f + 0.5f) * kWindowWidth));
	vRaster2.mY = static_cast<int>(std::floor((1.0f - (clipPoint2.mY * 0.5f + 0.5f)) * kWindowHeight));

	//int imageWidth = 320;
	//int imageHeight = 240;
	//vRaster1.mX = static_cast<int>(std::floor((clipPoint1.mX * 0.5f + 0.5f) * imageWidth));
	//vRaster1.mY = static_cast<int>(std::floor((1.0f - (clipPoint1.mY * 0.5f + 0.5f)) * imageHeight));

	//vRaster2.mX = static_cast<int>(std::floor((clipPoint2.mX * 0.5f + 0.5f) * imageWidth));
	//vRaster2.mY = static_cast<int>(std::floor((1.0f - (clipPoint2.mY * 0.5f + 0.5f)) * imageHeight));

	TextRenderer::print("vRaster1", vRaster1.mX, vRaster1.mY, inWorld);
	TextRenderer::print("vRaster1.mX: " + std::to_string(vRaster1.mX), 120, 80, inWorld);
	TextRenderer::print("vRaster1.mY: " + std::to_string(vRaster1.mY), 120, 100, inWorld);

	TextRenderer::print("vRaster2", vRaster2.mX, vRaster2.mY, inWorld);
	TextRenderer::print("vRaster2.mX: " + std::to_string(vRaster2.mX), 120, 140, inWorld);
	TextRenderer::print("vRaster2.mY: " + std::to_string(vRaster2.mY), 120, 160, inWorld);

	//vRaster1.mX += 100;
	//vRaster1.mY += 100;
	//vRaster2.mX += 100;
	//vRaster2.mY += 100;
	SetRenderViewPort(inWorld);
	SDL_RenderDrawLine(mpRenderer.get(), vRaster1.mX, vRaster1.mY, vRaster2.mX, vRaster2.mY);
}

void SdlRenderer::RenderDrawRect(int width, int height, int x, int y, const bool inWorld)
{

	SDL_Rect rect{x, y, width, height};

	SetRenderViewPort(inWorld);
	SDL_RenderDrawRect(mpRenderer.get(), &rect);
}

void SdlRenderer::extractAllPlanes()
{
	const Matrix44<float>& mat = kProjectionMatrix;

	mPlanes[0].set(mat[3][0] + mat[0][0], mat[3][1] + mat[0][1], mat[3][2] + mat[0][2], mat[3][3] + mat[0][3]); mPlanes[0].normalize();
	mPlanes[1].set(mat[3][0] - mat[0][0], mat[3][1] - mat[0][1], mat[3][2] - mat[0][2], mat[3][3] - mat[0][3]); mPlanes[1].normalize();

	mPlanes[2].set(mat[3][0] + mat[1][0], mat[3][1] + mat[1][1], mat[3][2] + mat[1][2], mat[3][3] + mat[1][3]); mPlanes[2].normalize();
	mPlanes[3].set(mat[3][0] - mat[1][0], mat[3][1] - mat[1][1], mat[3][2] - mat[1][2], mat[3][3] - mat[1][3]); mPlanes[3].normalize();

	mPlanes[4].set(mat[3][0] + mat[2][0], mat[3][1] + mat[2][1], mat[3][2] + mat[2][2], mat[3][3] + mat[2][3]); mPlanes[4].normalize();
	mPlanes[5].set(mat[3][0] - mat[2][0], mat[3][1] - mat[2][1], mat[3][2] - mat[2][2], mat[3][3] - mat[2][3]); mPlanes[5].normalize();
}

std::shared_ptr<SdlRenderer> SdlRenderer::initialize(std::shared_ptr<SDL_Renderer> renderer, const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight, const Matrix44<float>& projectionMatrix)
{
	auto sdlRenderer = std::make_shared<SdlRenderer>(renderer, windowWidth, windowHeight, canvasWidth, canvasHeight, projectionMatrix);

	sdlRenderer->extractAllPlanes();

	return sdlRenderer;
}

void SdlRenderer::SetRenderViewPort(bool inWorld)
{
	inWorld ?
		SDL_RenderSetViewport(mpRenderer.get(), &kViewPort) :
		SDL_RenderSetViewport(mpRenderer.get(), NULL);
}