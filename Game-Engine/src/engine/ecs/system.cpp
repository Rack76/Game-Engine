#include "System.h"

System::System(SystemManager* sysMgr, const SystemType& systemType)
{

}

bool System::addEntity(const EntityId& entity)
{
	return false;
}

bool System::hasEntity(const EntityId& entity)
{
	return false;
}

bool System::removeEntity(const EntityId& entity)
{
	return false;
}

bool System::fitsRequirement(const BitMask& bits)
{
	return false;
}

void System::purge()
{
}

void System::update(float dt)
{
}

void System::handleEvent(const EntityId& entity, const EntityEvent& event)
{
}
