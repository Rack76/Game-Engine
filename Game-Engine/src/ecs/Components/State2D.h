#pragma once

#include "../../math/MathConfig.h"
#include "../Component.h"
#include "../ECS_Types.h"

using namespace glm;

class State2D : Component
{
	State2D() : position(vec2(0, 0)), Component(ComponentType::State)
	{}

	void read(std::stringstream& stream);

	vec2 getPosition() { return position; }
	void setPosition(vec2 position) { this->position = position; }

private:
	vec2 position;
};