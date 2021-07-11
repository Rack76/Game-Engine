#include <cstdio>

#include "framework.h"

#include "engine/render/renderer.h"

#include <SDL_events.h>
#include <SDL_timer.h>

GameFramework::GameFramework(engine::display::Window& window)
{
	engine::render::Init(window);
}

GameFramework::~GameFramework()
{
	engine::render::Shutdown();
}

void GameFramework::Run()
{

	while (true)
	{
		SDL_Event sdlEvent;
		//#todo remove sdl specifics, move into engine events or replace this with the events system
		while (SDL_PollEvent(&sdlEvent) != 0)
		{

		}

		engine::render::SetClearColour({ 255, 0, 0, 255 });
		engine::render::Clear();
		engine::render::DrawQuad({ 0, 0, 255, 255 }, { 100, 100 }, 100, 100);
		engine::render::Present();
	}


}
