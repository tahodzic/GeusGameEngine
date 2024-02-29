#pragma once

#include <stdint.h>

class IFont
{
public:

    virtual ~IFont() {}

	virtual void SetRenderViewPort(bool inWorld) = 0;

	virtual int SizeUTF8(const char* text, int* w, int* h) = 0;

	virtual void RenderUTF8_Solid(const char* text, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;

	virtual void CreateTextureFromSurface() = 0;

	virtual void FreeSurface() = 0;

	virtual void DestroyTexture() = 0;

	virtual int RenderCopy() = 0;

	virtual void SetDestRect(int x, int y, int w, int h) = 0;
};