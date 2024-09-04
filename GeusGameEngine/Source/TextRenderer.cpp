#include "TextRenderer.h"


#include <SDL.h>
#include <SDL_ttf.h>

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
}

static std::shared_ptr<IMediaLayer> sMediaLayer;

void TextRenderer::Initialize(std::shared_ptr<IMediaLayer> mediaLayer)
{
	sMediaLayer = mediaLayer;
}

void TextRenderer::print(std::string_view text, int x, int y, bool inWorld)
{
	int fontWidth, fontHeight;

	SDL_Color White = { 255, 255, 255 };

	sMediaLayer->SetRenderViewPort(inWorld);

	sMediaLayer->SizeUTF8(text.data(), fontWidth, fontHeight);

	sMediaLayer->RenderUTF8_Solid(text.data(), White.r, White.g, White.b, White.a);

	sMediaLayer->CreateTextureFromSurface();

	sMediaLayer->SetDestRect(x - fontWidth, y - fontHeight, fontWidth, fontHeight);

	sMediaLayer->RenderCopy();

	sMediaLayer->FreeSurface();

	sMediaLayer->DestroyTexture();
}