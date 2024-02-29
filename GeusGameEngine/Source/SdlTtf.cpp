#pragma once

#include "SdlTtf.h"
#include "IFont.h"

#include <SDL_ttf.h>

#include <stdint.h>


SdlTtf::SdlTtf(std::shared_ptr<TTF_Font> font, std::shared_ptr<SDL_Renderer> renderer) :
	mpFont(font),
	mpRenderer(renderer),
	mRectSrc(),
	mRectDest(),
	mTexture(nullptr),
	mSurface(nullptr),
	mFontWidth(0),
	mFontHeight(0)
{
}

SdlTtf::~SdlTtf() = default;



void SdlTtf::SetRenderViewPort(bool inWorld)
{
	static const SDL_Rect rect{ 100,100,640,480 };
	
	inWorld ?
		SDL_RenderSetViewport(mpRenderer.get(), &rect) :
		SDL_RenderSetViewport(mpRenderer.get(), NULL);
}

int SdlTtf::SizeUTF8(const char* text, int* w, int* h)
{
	return TTF_SizeUTF8(mpFont.get(), text, w, h);
}

void SdlTtf::RenderUTF8_Solid(const char* text, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_Color c{ r,g,b,a };

	SDL_Color bg{};

	auto p = mpFont.get();

	auto t = TTF_RenderUTF8_Shaded(p, text, c, bg);

	mSurface.reset(t);
}

void SdlTtf::FreeSurface()
{
	mSurface.reset();
}

void SdlTtf::DestroyTexture()
{
	mTexture.reset();
}

int SdlTtf::RenderCopy()
{
	return SDL_RenderCopy(mpRenderer.get(), mTexture.get(), NULL, &mRectDest);
}

void SdlTtf::SetDestRect(int x, int y, int w, int h)
{
	mRectDest.x = x;
	mRectDest.y = y;
	mRectDest.w = w;
	mRectDest.h = h;
}

void SdlTtf::CreateTextureFromSurface()
{
	mTexture.reset(SDL_CreateTextureFromSurface(mpRenderer.get(), mSurface.get()));
}
