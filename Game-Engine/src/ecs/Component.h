#pragma once

#include "ECS_Types.h"
#include <sstream>

class Component
{
public:
	Component(const ComponentType& ct) : m_ct(ct) {}
	ComponentType getType() { return m_ct; }

	friend std::stringstream& operator>>(std::stringstream& stream, Component& component)
	{}
private:
	ComponentType m_ct;
};