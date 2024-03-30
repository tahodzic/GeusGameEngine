#pragma once

#include "MediaLayer.h"

#include "SdlTtf.h"
#include "SdlRenderer.h"
#include "SdlDeleter.h"
#include "TtfDeleter.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <stdexcept>

MediaLayer::MediaLayer(std::shared_ptr<IRenderer> rendererHandler, std::shared_ptr<IFont> fontHandler)
	: mRendererHandler(rendererHandler), mFontHandler(fontHandler)
{
}

MediaLayer::~MediaLayer()
{
}

static std::shared_ptr<SDL_Renderer> CreateRenderer(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw std::runtime_error("SDL_Init failed.");
	}

	SDL_Window* win = SDL_CreateWindow(title.data(), windowsPosX, windowsPosY, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);

	std::shared_ptr<SDL_Renderer> sdlRenderer(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED), SdlDeleter::Deleter());

	return sdlRenderer;
}

static void SetupRenderer(std::shared_ptr<SDL_Renderer> renderer)
{
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderClear(renderer.get());

	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, SDL_ALPHA_OPAQUE);
}

static std::shared_ptr<IRenderer> InitializeSdlRenderer(std::shared_ptr<SDL_Renderer> renderer,
	const int& windowWidth, const int& windowHeight, const int& canvasWidth, const int& canvasHeight)
{
	SetupRenderer(renderer);

	return SdlRenderer::Initialize(renderer, windowWidth, windowHeight, canvasWidth, canvasHeight);
}

static std::shared_ptr<IFont> InitializeFont(std::shared_ptr<SDL_Renderer> renderer)
{
	if (TTF_Init())
	{
		throw std::runtime_error("TTF_Init failed.");
	}

	auto exeBasePath = SDL_GetBasePath();

	if (!exeBasePath)
	{
		throw std::runtime_error("Couldn't get the base path for opening the font.");
	}

	std::string path = exeBasePath;

	SDL_free(exeBasePath);

	path += "..\\..\\..\\..\\Resource\\OpenSans-Bold.ttf";

	auto ttf = TTF_OpenFont(path.c_str(), 12);

	std::shared_ptr<TTF_Font> font(ttf, TtfDeleter::Deleter());

	return std::make_shared<SdlTtf>(font, renderer);
}

std::shared_ptr<MediaLayer> MediaLayer::CreateAndSetup(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight,
	const int& canvasWidth, const int& canvasHeight)
{
	auto ren = CreateRenderer(title, windowsPosX, windowsPosY, windowWidth, windowHeight);

	auto renderControl = InitializeSdlRenderer(ren, windowWidth, windowHeight, canvasWidth, canvasHeight);

	auto fontControl = InitializeFont(ren);

	return std::make_shared<MediaLayer>(renderControl, fontControl);
}

void MediaLayer::PrepareRenderer() const
{
	mRendererHandler->SetDrawColor(0, 0, 0, 255/*SDL_ALPHA_OPAQUE*/);

	mRendererHandler->RenderClear();

	mRendererHandler->SetDrawColor(255, 255, 255, 255/*SDL_ALPHA_OPAQUE*/);
}

std::shared_ptr<IRenderer> MediaLayer::GetRenderer() const
{
	return mRendererHandler;
}

std::shared_ptr<IFont> MediaLayer::GetFontHandler() const
{
	return mFontHandler;
}

void MediaLayer::Render() const
{
	mRendererHandler->RenderPresent();
}

void MediaLayer::RenderLine(
	const Vector3<float>& vector1,
	const Vector3<float>& vector2,
	const Matrix44<float>& worldToCameraMatrix,
	const bool inWorld) const
{
	mRendererHandler->RenderDrawLine(
		vector1,
		vector2,
		worldToCameraMatrix,
		inWorld);
}

void MediaLayer::RenderPolygon(
	const std::vector<Vector3<float>>& vertices,
	const std::vector<int>& indices,
	const Matrix44<float>& worldToCameraMatrix,
	const Matrix44<float>& localToWorldMatrix,
	const bool inWorld) const
{
	mRendererHandler->RenderPolygon(
		vertices,
		indices,
		worldToCameraMatrix,
		localToWorldMatrix,
		inWorld);
}

void MediaLayer::RenderRect(const int width, const int height, const int x, const int y, const bool inWorld) const
{
	mRendererHandler->RenderDrawRect(width, height, x, y, inWorld);
}

void MediaLayer::SetRenderViewPort(const bool inWorld) const
{
	mRendererHandler->SetRenderViewPort(inWorld);
}

void MediaLayer::SizeUTF8(std::string_view text, int& w, int& h) const
{
	mFontHandler->SizeUTF8(text.data(), &w, &h);
}

void MediaLayer::RenderUTF8_Solid(std::string_view text, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) const
{
	mFontHandler->RenderUTF8_Solid(text.data(), r, g, b, a);
}

void MediaLayer::CreateTextureFromSurface() const
{
	mFontHandler->CreateTextureFromSurface();
}

void MediaLayer::SetDestRect(const int x, const int y, const int w, const int h) const
{
	mFontHandler->SetDestRect(x, y, w, h);
}

void MediaLayer::RenderCopy() const
{
	mFontHandler->RenderCopy();
}

void MediaLayer::FreeSurface() const
{
	mFontHandler->FreeSurface();
}

void MediaLayer::DestroyTexture() const
{
	mFontHandler->DestroyTexture();
}