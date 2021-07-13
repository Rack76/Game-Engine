#include "engine.h"
#include "events.h"
#include "eventloop_sdl.h"

namespace ge::engine {
	namespace {
		ge::events::EventEmitterVoid functions[coreFunctions::totalFunctions];
	}
	void Run() {
		bool done = false;
		functions[0].send();
		while (!done) {
			functions[1].send();
			ge::eventloop_sdl::processAll(done);
			if (done) break;
			functions[2].send();
			functions[3].send();
			for (int i = 4; i <= 8; i++) {
				functions[i].send();
			}
			functions[9].send();
			functions[10].send();
		}
		functions[11].send();
	}

	void coreFunctions::addFunction(coreFunctions::Type const& type, void(*func)(void)) {
		functions[static_cast<int>(type)].add(func);
	}
}