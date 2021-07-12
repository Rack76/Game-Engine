#include "System.h"

System::System(SystemManager* sysMgr, const SystemType& systemType) : sysMgr(sysMgr), sysType(systemType)
{

}

System::~System()
{
	purge();
}

bool System::addEntity(const EntityId& entity)
{
	if (hasEntity(entity))
		return false;

	entityList.emplace_back(entity);
	return true;
}

bool System::hasEntity(const EntityId& entity)
{
	auto itr = std::find_if(entityList.begin(), entityList.end(),
		[&entity](unsigned int m_entity) {return m_entity == entity; });
	return (itr == entityList.end());
}

bool System::removeEntity(const EntityId& entity)
{
	auto itr = std::find_if(entityList.begin(), entityList.end(), 
		[entity](EntityId& id) {return id == entity; });

	if (itr == entityList.end())
		return false;

	entityList.erase(itr);
	return true;
}

bool System::fitsRequirement(const BitMask& bits)
{
	return std::find_if(requiredComponents.begin(), requiredComponents.end(), 
		[&bits](const BitMask& m_bits) {return bits.getMask() == m_bits.getMask(); }) != requiredComponents.end();
}

void System::purge()
{
	entityList.clear();
}

