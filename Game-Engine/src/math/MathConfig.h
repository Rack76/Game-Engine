#pragma once

#include "Math.h"
#include "glm/glm.hpp"

class MathConfig
{
public:
	void useGLM()
	{
		using namespace glm;
	}

	void useMyImplementation()
	{
		using namespace Math;
	}
};