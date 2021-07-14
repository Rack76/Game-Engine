#ifndef INCLUDED_WINDOW_HPP
#define INCLUDED_WINDOW_HPP

#include<string>
#include<memory>
#include<SDL.h>

namespace Engine {
	class Window {
	public:
		operator SDL_Window* () const noexcept;

		/* Cannot take a string view because it might not be null-terminated. */
		/* We could add a char const* overload but I really doubt it matters */
		Window(std::string const& _title, unsigned _width, unsigned _height);
		~Window() = default;

		Window(Window const&) = delete;
		Window& operator=(Window const&) = delete;

	private:
		std::unique_ptr<
			SDL_Window,
			decltype([](SDL_Window* _window) { SDL_DestroyWindow(_window); })
		> window;

	};
}

#endif