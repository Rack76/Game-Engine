#include "eventloop.h"
#include "events.h"
#include "engine.h"
#include <SDL.h>
#include <map>

namespace ge::eventloop_sdl {
	std::map<Uint32, ge::events::EventEmitter<SDL_Event const&>> sdlevents;

	void processAll(bool& done) {
		static SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			sdlevents[e.type].send(e);
			if (e.type == SDL_EventType::SDL_QUIT) {
				done = true;
				return;
			}
		}
	}
	void addEvent(SDL_EventType type, void(*func)(SDL_Event const& e)) {
		sdlevents[type].add(func);
	}
}