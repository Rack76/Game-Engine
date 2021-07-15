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

ge::Application::~Application() {}

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

void ge::Application::onEveryTick(int order, void(*func)(void)) {
	ge::userFunctions::addFunction(func, order);
}
