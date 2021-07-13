#include "eventloop_sdl.h"
#include "events.h"
#include "engine.h"
#include <SDL.h>
#include <map>

namespace ge::eventloop_sdl {
	std::map<SDL_EventType, ge::events::EventEmitter<SDL_Event const&>> sdlevents;

	void processAll(bool& done) {
		static SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			//sdlevents[e.type]
			switch (e.type)
			{
			case SDL_QUIT:
				done = true;
				return;
			case SDL_EventType::SDL_MOUSEBUTTONDOWN:

			}
		}
	}
}