#pragma once

#include <SDL.h>
#include "WindowGLFW.h"

class WindowGLFW_OpenGL : public WindowGLFW
{
public:
	void bindContext();
private:
	SDL_GLContext context;
};