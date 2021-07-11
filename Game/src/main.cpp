#include "framework.h"
#include "engine/window/window.h"

int main()
{
	engine::display::Window window("game", 1280, 720);

	GameFramework framework(window);
	framework.Run();
}