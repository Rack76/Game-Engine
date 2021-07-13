#pragma once

#include "NewRenderer.h"
#include "window/Window.h"

class Renderer3D : public Renderer
{
public:
	Renderer3D(Window* window, SystemManager* sysMgr, const SystemType& systemType) : Renderer(window, sysMgr, systemType)
	{

	}
};