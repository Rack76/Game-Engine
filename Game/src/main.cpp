#include "framework.h"
#include "engine/window/window.h"

int main()
{
	engine::display::Window window("game", 1280, 720);

	std::unique_ptr<GameFramework> framework = std::make_unique<GameFramework>(window);
	framework->Run();
}