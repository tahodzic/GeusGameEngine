#pragma once

#include "IMediaLayer.h"

#include <string>

class TextRenderer
{
public:
	TextRenderer();

	~TextRenderer();
	
	static void Initialize(std::shared_ptr<IMediaLayer> mediaLayer);

	static void print(std::string_view text, int x, int y, bool inWorld);
};

