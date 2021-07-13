#include "engine.h"
#include "events.h"
#include "eventloop_sdl.h"
#include "userfunctions.h"

namespace ge::engine {
	namespace {
		ge::events::EventEmitterVoid functions[coreFunctions::totalFunctions];
		void send(coreFunctions::Type type) {
			functions[static_cast<int>(type)].send();
		}
	}
	void Run() {
		using Type = coreFunctions::Type;
		
		bool done = false;
		send(Type::atStartup);
		while (!done) {
			send(Type::first);

			send(Type::beforeInput);
			ge::eventloop_sdl::processAll(done);
			if (done) break;
			send(Type::afterInput);

			send(Type::beforeUser);
			ge::userFunctions::sendAll();
			send(Type::afterUser);

			send(Type::last);
		}
		send(Type::atExit);
	}

	void coreFunctions::addFunction(coreFunctions::Type const& type, void(*func)(void)) {
		functions[static_cast<int>(type)].add(func);
	}
}