#include "window.h"
#include "renderer.h"
#include "SDL.h"
#include <cstdlib>

namespace ge::window {
	void atExit() {
		if (ge::renderer::renderer) SDL_DestroyRenderer(ge::renderer::renderer);
		if (window) SDL_DestroyWindow(window);
	}

	bool Init(const char* title, int width, int height) {
		static bool ifInit = false;
		if (ifInit) return true;
		std::atexit(atExit);
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
		window = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_SHOWN);

		if (!window) return false;
		ge::renderer::renderer = SDL_CreateRenderer(window, -1, 0);
		ifInit = true;
		return true;
	}

	bool Init() {
		return ge::window::Init("", 1280, 720);
	}
	void SetTitle(const char* title) {
		SDL_SetWindowTitle(window, title);
	}
}

