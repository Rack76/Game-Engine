#pragma once

#include "ECS_Types.h"
#include <sstream>

class Component
{
public:
	Component(const ComponentType& ct) : m_ct(ct) {}
	ComponentType getType() { return m_ct; }

	friend std::stringstream& operator>>(std::stringstream& stream, Component& component)
	{
		component.read(stream);
		return stream;
	}

	virtual void read(std::stringstream& stream) = 0;
protected:
	ComponentType m_ct;
};