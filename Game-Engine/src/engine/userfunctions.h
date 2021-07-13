#pragma once
namespace ge {
	namespace userFunctions {
		void addFunction(int order, void(*func)(void));
		void sendAll();
	}
}