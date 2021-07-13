#pragma once

#include "Renderer3D.h"

class RendererOpenGL : public Renderer3D
{
public:
	RendererOpenGL(Window* window, SystemManager* sysMgr, const SystemType& systemType) : Renderer3D(window, sysMgr, systemType)
	{

	}
};