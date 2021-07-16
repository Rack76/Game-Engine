#include "game.h"
#include "engine/window.h"
#include "engine/renderer.h"
#include "engine/engine.h"
#include "engine/eventloop.h"
#include "engine/userfunctions.h"
#include <cstdlib>

ge::Application::Application() {
	if (ge::window::Init()) return; //successful Init
	//failed
	std::exit(0);
}

ge::Application::~Application() {
	if (ge::window::window) SDL_DestroyWindow(ge::window::window);
	if (ge::renderer::renderer) SDL_DestroyRenderer(ge::renderer::renderer);
	SDL_Quit();
}

void ge::Application::Run() {
	ge::engine::Run();
}

void ge::Application::on(EventType type, void(*func)(SDL_Event const& e)) {
	switch (type) {
	case ge::EventType::SDLall:
		ge::eventloop_sdl::addAllEvent(func);
		break;
	}
}

void ge::Application::on(SDL_EventType type, void(*func)(SDL_Event const& e)) {
	ge::eventloop_sdl::addEvent(type, func);
}

SDL_Renderer* ge::Application::GetRenderer() {
	return ge::renderer::renderer;
}

SDL_Window* ge::Application::GetWindow() {
	return ge::window::window;
}

void ge::Application::onEveryTick(int order, void(*func)(void)) {
	ge::userFunctions::addFunction(func, order);
}

void ge::Application::setTitle(std::string title) {
	ge::window::SetTitle(title.c_str());
}
