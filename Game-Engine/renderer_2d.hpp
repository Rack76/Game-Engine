#ifndef INCLUDED_RENDERER_2D_HPP
#define INCLUDED_RENDERER_2D_HPP

#include"window.hpp"
#include"types.hpp"
#include<SDL.h>

namespace Engine {
	class Renderer_2d {
	public:
		enum struct Primitive {
			quad,
			/* More in the future */
		};

		template<Primitive>
		void render(auto&&...) = delete;

		template<>
		void render<Primitive::quad>(Quad const& _quad, Colour const& _colour);

		void clear(Colour const& _colour = {});
		void render_present();

		operator SDL_Renderer* () const noexcept;

		Renderer_2d(Window const& _window);
		~Renderer_2d() = default;

		Renderer_2d(Renderer_2d const&) = delete;
		Renderer_2d& operator=(Renderer_2d const&) = delete;
	
	private:
		std::unique_ptr<
			SDL_Renderer,
			decltype([](SDL_Renderer* _renderer) { SDL_DestroyRenderer(_renderer); })
		> renderer;

	};
}

#endif