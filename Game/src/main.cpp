#include <memory>
#include <iostream>

#include "game/framework.h"
#include "engine/events/events.hpp"

#include "engine/window/window.h"
#include "engine/render/renderer.h"

struct X : Event_emitter<int, double> {
	void emit() {
		post_event(5);
		post_event(1.0);
	}
};

int main(int argc, char* argv[])
{
	engine::display::Window window("game", 1280, 720);

	GameFramework framework(window);
	framework.Run();
}