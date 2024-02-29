#pragma once

#include "MediaLayer.h"
#include "SdlLibrary.h"

MediaLayer::MediaLayer() {}

MediaLayer& MediaLayer::getInstance()
{
	 static MediaLayer instance;
	 return instance;
}

void MediaLayer::initialize(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight,
	const int& canvasWidth, const int& canvasHeight,
	const Matrix44<float>& projectionMatrix)
{
	mpGraphicsLibrary = std::make_unique<SdlLibrary>();

	mpGraphicsLibrary->Initialize(title, windowsPosX, windowsPosY, windowWidth, windowHeight, canvasWidth, canvasHeight, projectionMatrix);
}

void MediaLayer::prepareRenderer()
{
	mpGraphicsLibrary->GetRendererHandler()->SetDrawColor(0, 0, 0, 255/*SDL_ALPHA_OPAQUE*/);

	mpGraphicsLibrary->GetRendererHandler()->RenderClear();

	mpGraphicsLibrary->GetRendererHandler()->SetDrawColor(255, 255, 255, 255/*SDL_ALPHA_OPAQUE*/);
}

void MediaLayer::render()
{
	mpGraphicsLibrary->GetRendererHandler()->RenderPresent();
}

void MediaLayer::renderLine(
	const Vector3Custom<float>& vector1,
	const Vector3Custom<float>& vector2,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld)
{
	mpGraphicsLibrary->GetRendererHandler()->RenderDrawLine(
		vector1,
		vector2,
		worldToCameraMatrix,
		inWorld);
}

void MediaLayer::renderPolygon(
	const std::vector<Vector3Custom<float>>& vertices,
	const std::vector<int>& indices,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld)
{
	mpGraphicsLibrary->GetRendererHandler()->RenderPolygon(
		vertices,
		indices,
		worldToCameraMatrix,
		inWorld);
}