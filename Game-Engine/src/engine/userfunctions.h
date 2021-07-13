#pragma once
namespace ge {
	namespace userFunctions {
		void addFunction(void(*func)(void), int order);
		void sendAll();
	}
}