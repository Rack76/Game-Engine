#include <cstdio>

#include "framework.h"

#include "engine/render/renderer.h"

GameFramework::GameFramework()
{
	engine::renderer::Init();
}

GameFramework::~GameFramework()
{
	printf("dtor");
	engine::renderer::Shutdown();
}
