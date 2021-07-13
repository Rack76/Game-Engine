#pragma once

#include "../NewRenderer.h"

class Window
{
	virtual void bindContext() = 0;
protected:
	Renderer* renderer;
};