#ifndef GAME_FRAMEWORK_H
#define GAME_FRAMEWORK_H

#include <memory>
#include <functional>

class Game;
union SDL_Event; //#todo sdl events still need wrapping

namespace engine
{
	namespace display
	{
		class Window;
	}
}

class GameFramework
{
public:

	GameFramework(engine::display::Window&);
	~GameFramework();

	void Run();

	static void AddEvent(const uint32_t eventId, std::function<void(const SDL_Event&)> cb);

private:
	std::unique_ptr<Game> m_game;
};

#endif