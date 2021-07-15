#include "game.h"
#include <SDL.h>
#include <iostream>
#include <vector>
ge::Application app;
SDL_Renderer* r = app.GetRenderer();
constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
std::vector<SDL_Point> clicks;
int main(int argc, char* args[])
{
	app.on(SDL_EventType::SDL_MOUSEBUTTONDOWN, [](SDL_Event const& e) {
		int x = e.button.x;
		int y = e.button.y;
		clicks.push_back({ x,y });
		});
	app.onEveryTick(0, []() {
		SDL_SetRenderDrawColor(r, 0, 255, 0, 0xFF);
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		if (clicks.size() > 1) {
			int x = clicks[0].x;
			int y = clicks[0].y;
			SDL_Point p1 = clicks[0];
			for (int i = 1; i < clicks.size(); i++) {
				SDL_Point const& p2 = clicks[i];
				SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
				p1 = p2;
			}
		}
		SDL_RenderPresent(r);
		});

	app.Run();
	return 0;
}