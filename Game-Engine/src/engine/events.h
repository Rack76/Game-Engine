#pragma once
#include <vector>
namespace ge {
	namespace events {
		template<typename... Parameters>
		class EventEmitter {
		public:
			void add(void(*func)(Parameters...)) {
				funcs.push_back(func);
			}
			void send(Parameters... p) {
				const int size = funcs.size();
				for (int i = 0; i < size; i++) {
					funcs[i](p...);
				}
			}
		private:
			std::vector<void(*)(Parameters...)> funcs;
		};
		class EventEmitterVoid {
		public:
			void add(void(*func)(void)) {
				funcs.push_back(func);
			}
			void send() {
				const int size = funcs.size();
				for (int i = 0; i < size; i++) {
					funcs[i]();
				}
			}
		private:
			std::vector<void(*)(void)> funcs;
		};
	}
}