#ifndef GAME_FRAMEWORK_H
#define GAME_FRAMEWORK_H


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
};

#endif