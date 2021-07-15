#pragma once

#include "../../math/MathConfig.h"
#include "../Component.h"
#include "../ECS_Types.h"

using namespace glm;

class State2D : public Component
{
public:
	State2D() : position(vec2(0, 0)), Component(ComponentType::State2D)
	{}

	void read(std::stringstream& stream);

	vec2 getPosition() { return position; }
	void setPosition(vec2 position) { this->position = position; }

private:
	vec2 position;
};