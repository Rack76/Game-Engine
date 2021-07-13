#pragma once
namespace ge {
	namespace engine {
		void Run();
		namespace coreFunctions {
			enum class Type {
				atStartup = 0,
				
				first = 1,
				beforeInput = 2,
				//usercode input will be called here
				afterInput = 3,
				beforeUser = 4,
				//usercode functions will be called here
				afterUser = 5,
				last = 6,

				atExit = 7
			};
			constexpr int totalFunctions = 8;
			void addFunction(coreFunctions::Type const& type, void(*func)(void));
		}
	}
}