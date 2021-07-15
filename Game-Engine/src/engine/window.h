#pragma once
#include <SDL.h>
namespace ge {
	namespace window {
		inline SDL_Window* window;
		bool Init(const char* title, int width, int height);
		bool Init();
		void SetTitle(const char* title);
	}
}