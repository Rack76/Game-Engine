#include "userfunctions.h"
#include <map>
#include "events.h"
#include "engine.h"

namespace ge::userFunctions {
	namespace {
		struct temp {
			int order;
			void (*func)(void);
		};
		std::map<int, ge::events::EventEmitterVoid> userfuncs;
		std::vector<temp> toAdd;
		void addNewFunctions() {
			for (auto x : toAdd) {
				userfuncs[x.order].add(x.func);
			}
			toAdd.clear();
		}
		void sendAllFunctions() {
			for (auto it = userfuncs.begin(); it != userfuncs.end(); ++it) {
				it->second.send();
			}
		}
	}
	void addFunction(void(*func)(void), int order) {
		toAdd.push_back({ order, func });
	}
	void sendAll() {
		sendAllFunctions();
		addNewFunctions();
	}
}