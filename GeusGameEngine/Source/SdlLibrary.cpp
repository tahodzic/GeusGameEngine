#pragma once

#include "SdlLibrary.h"
#include "SdlTtf.h"
#include "SdlRenderer.h"
#include "SdlDeleter.h"
#include "TtfDeleter.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <stdexcept>

static std::shared_ptr<SDL_Renderer> CreateRenderer(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw std::runtime_error("SDL_Init failed.");
	}

	SDL_Window* win = SDL_CreateWindow(title.data(), windowsPosX, windowsPosY, windowWidth, windowHeight, 0);

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

	return SdlRenderer::initialize(renderer, windowWidth, windowHeight, canvasWidth, canvasHeight);
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

SdlLibrary::SdlLibrary(std::shared_ptr<IRenderer> rendererControl, std::shared_ptr<IFont> fontControl) : mpRendererHandler(rendererControl), mpFontHandler(fontControl)
{
}

SdlLibrary::~SdlLibrary()
{
}

std::unique_ptr<SdlLibrary> SdlLibrary::CreateAndSetup(const std::string_view title,
	const int& windowsPosX, const int& windowsPosY,
	const int& windowWidth, const int& windowHeight,
	const int& canvasWidth, const int& canvasHeight)
{
	auto ren = CreateRenderer(title, windowsPosX, windowsPosY, windowWidth, windowHeight);

	auto renderControl = InitializeSdlRenderer(ren, windowWidth, windowHeight, canvasWidth, canvasHeight);

	auto fontControl = InitializeFont(ren);

	return std::make_unique<SdlLibrary>(renderControl, fontControl);
}