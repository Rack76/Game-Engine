#pragma once
#include <SDL.h>
#include <string>
namespace ge {
	enum class EventType {
		SDLall,
	};
	class Application {
	public:
		Application();
		~Application();
		void Run();
		void on(EventType type, void(*func)(SDL_Event const& e));
		//for more info about SDL_EventType https://wiki.libsdl.org/SDL_EventType
		void on(SDL_EventType type, void(*func)(SDL_Event const& e));
		
		
		//if multiple functions on same order is added they are
		//called in the order they were added
		void onEveryTick(int order, void(*func)(void));
		void setTitle(std::string title);
		//for drawing functions https://wiki.libsdl.org/CategoryRender
		SDL_Renderer* GetRenderer();
		SDL_Window* GetWindow();
	};
}