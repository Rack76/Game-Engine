#include "../window.h"

#include <string_view>

#include <SDL.h>
//#include <SDL_video.h>

namespace engine
{
	namespace display
	{
		Window::Window(std::string_view windowName, const uint16_t width, const uint16_t height)
			: m_windowName(windowName)
			, m_width(width)
			, m_height(height)
		{
			SDL_Init(SDL_INIT_VIDEO); //should be moved out somewhere, not sure what happens when creating multiple windows with sdl
			SDL_Window* sdlWindow = SDL_CreateWindow(windowName.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

			//handle sdlWindow nullptr

			m_handle = sdlWindow;
		}

		Window::~Window()
		{
			SDL_DestroyWindow(static_cast<SDL_Window*>(m_handle));
		}

		void UpdateWindow(Window& window)
		{
			//SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window.GetHandle()));
		}

	}
}