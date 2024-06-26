#pragma once

#include "MediaLayer.h"

#include <string>

class TextRenderer
{
public:
	TextRenderer();

	~TextRenderer();
	
	static void Initialize(std::shared_ptr<MediaLayer> mediaLayer);

	static void print(std::string_view text, int x, int y, bool inWorld);
};

