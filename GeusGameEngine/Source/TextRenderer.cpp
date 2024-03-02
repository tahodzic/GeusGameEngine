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

	MediaLayer::getInstance().SetRenderViewPort(inWorld);

	MediaLayer::getInstance().SizeUTF8(text.data(), fontWidth, fontHeight);

	MediaLayer::getInstance().RenderUTF8_Solid(text.data(), White.r, White.g, White.b, White.a);

	MediaLayer::getInstance().CreateTextureFromSurface();

	MediaLayer::getInstance().SetDestRect(x - fontWidth, y - fontHeight, fontWidth, fontHeight);

	MediaLayer::getInstance().RenderCopy();

	MediaLayer::getInstance().FreeSurface();

	MediaLayer::getInstance().DestroyTexture();
}