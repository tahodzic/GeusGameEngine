#pragma once

#include "MediaLayer.h"
#include "SdlLibrary.h"

MediaLayer::MediaLayer() {}

MediaLayer& MediaLayer::getInstance()
{
	 static MediaLayer instance;
	 return instance;
}

void MediaLayer::Initialize(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight,
	const int& canvasWidth, const int& canvasHeight,
	const Matrix44<float>& projectionMatrix)
{
	mpSdlLibrary = SdlLibrary::CreateAndSetup(title, windowsPosX, windowsPosY, windowWidth, windowHeight, canvasWidth, canvasHeight, projectionMatrix);
}

void MediaLayer::PrepareRenderer() const
{
	mpSdlLibrary->mpRendererHandler->SetDrawColor(0, 0, 0, 255/*SDL_ALPHA_OPAQUE*/);

	mpSdlLibrary->mpRendererHandler->RenderClear();

	mpSdlLibrary->mpRendererHandler->SetDrawColor(255, 255, 255, 255/*SDL_ALPHA_OPAQUE*/);
}

void MediaLayer::Render() const
{
	mpSdlLibrary->mpRendererHandler->RenderPresent();
}

void MediaLayer::RenderLine(
	const Vector3Custom<float>& vector1,
	const Vector3Custom<float>& vector2,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld) const
{
	mpSdlLibrary->mpRendererHandler->RenderDrawLine(
		vector1,
		vector2,
		worldToCameraMatrix,
		inWorld);
}

void MediaLayer::RenderPolygon(
	const std::vector<Vector3Custom<float>>& vertices,
	const std::vector<int>& indices,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld) const
{
	mpSdlLibrary->mpRendererHandler->RenderPolygon(
		vertices,
		indices,
		worldToCameraMatrix,
		inWorld);
}

void MediaLayer::RenderRect(const int width, const int height, const int x, const int y, const bool inWorld) const
{
	mpSdlLibrary->mpRendererHandler->RenderDrawRect(width, height, x, y, inWorld);
}

void MediaLayer::SetRenderViewPort(const bool inWorld) const
{
	mpSdlLibrary->mpRendererHandler->SetRenderViewPort(inWorld);
}

void MediaLayer::SizeUTF8(std::string_view text, int& w, int& h) const
{
	mpSdlLibrary->mpFontHandler->SizeUTF8(text.data(), &w, &h);
}

void MediaLayer::RenderUTF8_Solid(std::string_view text, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) const
{
	mpSdlLibrary->mpFontHandler->RenderUTF8_Solid(text.data(), r, g, b, a);
}

void MediaLayer::CreateTextureFromSurface() const
{
	mpSdlLibrary->mpFontHandler->CreateTextureFromSurface();
}

void MediaLayer::SetDestRect(const int x, const int y, const int w, const int h) const
{
	mpSdlLibrary->mpFontHandler->SetDestRect(x, y, w, h);
}

void MediaLayer::RenderCopy() const
{
	mpSdlLibrary->mpFontHandler->RenderCopy();
}

void MediaLayer::FreeSurface() const
{
	mpSdlLibrary->mpFontHandler->FreeSurface();
}

void MediaLayer::DestroyTexture() const
{
	mpSdlLibrary->mpFontHandler->DestroyTexture();
}