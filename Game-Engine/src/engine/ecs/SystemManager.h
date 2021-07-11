#pragma once

#include "BitMask.h"

class SystemManager
{
public:
	void entityModified(unsigned int entityId, const BitMask& mask);

	void addEvent(unsigned int entity, unsigned int event);

	void removeEntity(unsigned int entity);
};