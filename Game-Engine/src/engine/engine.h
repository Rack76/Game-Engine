#pragma once
#include "events.h"
namespace ge {
	namespace engine {
		void Run();
		namespace coreFunctions {
			enum class Type {
				atStartup = 0,
				beforeInputAndStart = 1,
				afterInput = 2,
				beforeUser = 3,
				user1 = 4,
				user2 = 5,
				user3 = 6,
				user4 = 7,
				user5 = 8,
				afterUser = 9,
				beforeEnd = 10,
				atExit = 11
			};
			constexpr int totalFunctions = 12;
			void addFunction(coreFunctions::Type const& type, void(*func)(void));
		}
	}
}