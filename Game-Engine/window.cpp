#include"window.hpp"

Engine::Window::Window(std::string const& _title, unsigned _width, unsigned _height) :
	window(SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN))
{ }

Engine::Window::operator SDL_Window* () const noexcept {
	return window.get();
}
