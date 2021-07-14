#include"renderer_2d.hpp"

Engine::Renderer_2d::Renderer_2d(Window const& _window) :
	renderer(SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED))
{ }

template<>
void Engine::Renderer_2d::render<Engine::Renderer_2d::Primitive::quad>(Quad const& _quad, Colour const& _colour) {
	SDL_SetRenderDrawColor(*this, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_Rect rect(_quad.x, _quad.y, _quad.width, _quad.height);
	SDL_RenderFillRect(*this, &rect);	
}


void Engine::Renderer_2d::clear(Colour const& _colour = {}) {
	SDL_SetRenderDrawColor(*this, _colour.r, _colour.g, _colour.b, _colour.a);
	SDL_RenderClear(*this);
}

void Engine::Renderer_2d::render_present() {
	SDL_RenderPresent(*this);
}

Engine::Renderer_2d::operator SDL_Renderer* () const noexcept {
	return renderer.get();
}
