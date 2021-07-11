#pragma once

#include "Math.h"
#include <glm/glm.hpp>

class MathConfig
{
public:
	static void useGLM()
	{
		using namespace glm;
	}

	static void useMyImplementation()
	{
		using namespace Math;
	}
};