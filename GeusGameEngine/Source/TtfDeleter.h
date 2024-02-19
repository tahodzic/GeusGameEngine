#pragma once

#include <SDL_ttf.h>

namespace TtfDeleter
{
	struct Deleter
	{
		void operator()(TTF_Font* ptr) const
		{
			if (ptr != nullptr) {
				TTF_CloseFont(ptr);
			}
		}
	};
}