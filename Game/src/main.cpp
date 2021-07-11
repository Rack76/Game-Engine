#include "game/framework.h"

#include "engine/window/window.h"

int main(int argc, char* argv[])
{
	engine::display::Window window("game", 1280, 720);

	GameFramework framework(window);
	framework.Run();
}