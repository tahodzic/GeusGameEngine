#pragma once

#include <SDL.h>

namespace SdlDeleter
{
	struct Deleter
	{
		void operator()(SDL_Texture* ptr) const
		{
			if (ptr != nullptr) {
				SDL_DestroyTexture(ptr);
			}
		}

		void operator()(SDL_Renderer* ptr) const
		{
			if (ptr != nullptr) {
				SDL_DestroyRenderer(ptr);
			}
		}

		void operator()(SDL_Surface* ptr) const
		{
			if (ptr != nullptr) {
				SDL_FreeSurface(ptr);
			}
		}
	};
}
