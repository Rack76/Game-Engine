#pragma once
#include <SDL.h>
namespace ge {
	namespace eventloop_sdl {
		void processAll(bool& done);
		void addEvent(SDL_EventType type, void(*func)(SDL_Event const& e));
		void addAllEvent(void(*func)(SDL_Event const& e));
	}
}