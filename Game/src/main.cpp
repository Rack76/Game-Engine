#include <memory>
#include <iostream>

#include "game/framework.h"
#include "engine/events/events.hpp"

struct X : Event_emitter<int, double> {
	void emit() {
		post_event(5);
		post_event(1.0);
	}
};

int main(int argc, char* argv[])
{
	GameFramework framework;


	X x;
	auto h1 = x.add_callback([](int) -> void { std::cout << "Received int event\n"; });
	auto h2 = x.add_callback([](double) { std::cout << "Received double event\n"; });

	x.emit();

}