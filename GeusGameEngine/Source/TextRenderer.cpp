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

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->SetRenderViewPort(inWorld);

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->SizeUTF8(text.data(), &fontWidth, &fontHeight);

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->RenderUTF8_Solid(text.data(), White.r, White.g, White.b, White.a);

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->CreateTextureFromSurface();

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->SetDestRect(x - fontWidth, y - fontHeight, fontWidth, fontHeight);

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->RenderCopy();

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->FreeSurface();

	MediaLayer::getInstance().mpGraphicsLibrary->GetFontHandler()->DestroyTexture();
}