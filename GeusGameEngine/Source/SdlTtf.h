#pragma once

#include "IFont.h"
#include "SdlDeleter.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdint.h>

#include <memory>

class SdlTtf : public IFont
{
public:
	SdlTtf(std::shared_ptr<TTF_Font> font, std::shared_ptr<SDL_Renderer> renderer);

	~SdlTtf();

	std::shared_ptr<TTF_Font> mpFont;

	std::shared_ptr<SDL_Renderer> mpRenderer;

	std::unique_ptr<SDL_Texture, SdlDeleter::Deleter> mTexture;

	std::unique_ptr<SDL_Surface, SdlDeleter::Deleter> mSurface;

	SDL_Rect mRectSrc;

	SDL_Rect mRectDest;

	int mFontWidth;

	int mFontHeight;

	int SizeUTF8(const char* text, int* w, int* h) override;

	void RenderUTF8_Solid(const char* text, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;

	void CreateTextureFromSurface() override;

	void FreeSurface() override;

	void DestroyTexture() override;

	int RenderCopy() override;

	void SetDestRect(int x, int y, int w, int h) override;
};

