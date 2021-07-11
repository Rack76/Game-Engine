#include "../renderer.h"

#include <SDL_render.h>

#include "../../../engine/window/window.h"

namespace
{
	SDL_Renderer* renderer;
}

namespace engine
{
	namespace render
	{
		void Init(display::Window& window) 
		{
			SDL_Window* sdlWindow = static_cast<SDL_Window*>(window.GetHandle());
			renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
		}

		void Shutdown() 
		{
			if (renderer)
			{
				SDL_DestroyRenderer(renderer);
			}
		}

		void Clear()
		{
			SDL_RenderClear(renderer);
		}

		void SetClearColour(const ColourRGBA colour)
		{
			SDL_SetRenderDrawColor(renderer, colour.m_r, colour.m_g, colour.m_b, colour.m_a);
		}

		void Present()
		{
			SDL_RenderPresent(renderer);
		}

		void DrawQuad(const ColourRGBA colour, const Position pos, const uint16_t width, const uint16_t height)
		{
			SDL_SetRenderDrawColor(renderer, colour.m_r, colour.m_g, colour.m_b, colour.m_a);
			SDL_Rect rect;
			rect.x = pos.m_x;
			rect.y = pos.m_y;
			rect.w = width;
			rect.h = height;

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}