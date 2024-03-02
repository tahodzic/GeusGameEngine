#include "TextRenderer.h"


#include <SDL.h>
#include <SDL_ttf.h>

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::print(std::string_view text, int x, int y, bool inWorld)
{
	int fontWidth, fontHeight;

	SDL_Color White = { 255, 255, 255 };

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->SetRenderViewPort(inWorld);

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->SizeUTF8(text.data(), &fontWidth, &fontHeight);

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->RenderUTF8_Solid(text.data(), White.r, White.g, White.b, White.a);

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->CreateTextureFromSurface();

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->SetDestRect(x - fontWidth, y - fontHeight, fontWidth, fontHeight);

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->RenderCopy();

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->FreeSurface();

	MediaLayer::getInstance().mpSdlLibrary->mpFontHandler->DestroyTexture();
}