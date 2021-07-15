#include "game.h"
#include <SDL.h>
#include <iostream>
ge::Application app;
SDL_Renderer* r = app.GetRenderer();
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
int main(int argc, char* args[])
{
	
	app.onEveryTick(0, []() {
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		SDL_RenderDrawLine(r, 100, 100, 200, 200);
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(r, &fillRect);
		});

	app.Run();
	return 0;
}