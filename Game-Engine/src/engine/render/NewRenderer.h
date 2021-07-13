#pragma once

#include "../ecs/System.h"

class Renderer : public System
{
public:
	Renderer(Window* window, SystemManager* sysMgr, const SystemType& systemType) : System(sysMgr, systemType), window(window)
	{

	}
	virtual void swapBuffers() = 0;
	virtual void draw() = 0;

protected:
	Window* window;
};