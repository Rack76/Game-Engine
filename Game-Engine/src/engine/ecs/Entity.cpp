#include "Entity.h"

EntityManager::EntityManager(SystemManager* sysMgr) : sysMgr(sysMgr), counter(0)
{
	componentFactory.reserve(N_COMPONENT_TYPES);
	addComponentType<State2D>(ComponentType::State2D);
}

EntityManager::~EntityManager()
{
	purge();
}

void EntityManager::addEntity(const BitMask& mask)
{
	unsigned int entity = counter;
	entityContainer.emplace(entity, EntityData(0, ComponentContainer()));

	counter++;

	for (unsigned int i = 0; i < N_COMPONENT_TYPES; i++)
	{
		if (mask.getBit(i)) { addComponent(entity, (ComponentType)i); }
	}

	sysMgr->entityModified(entity, mask);
	sysMgr->addEvent(entity, (EntityID)EntityEvent::Spawned);
}

void EntityManager::addEntity(const std::string& fileStr)
{
}

bool EntityManager::removeEntity(const EntityId& entity)
{
	auto itr = entityContainer.find(entity);
	if (itr == entityContainer.end())
		return false;

	while (itr->second.second.begin() != itr->second.second.end())
	{
		delete itr->second.second.back();
		itr->second.second.pop_back();
	}

	entityContainer.erase(itr);
	sysMgr->removeEntity(entity);
	return true;
}

void EntityManager::addComponent(const EntityId& entity, const ComponentType& componentType)
{
}

void EntityManager::removeComponent(const EntityId& entity, const ComponentType& componentType)
{
}

bool EntityManager::hasComponent(const EntityId& entity, const ComponentType& componentType)
{
	return false;
}

void EntityManager::purge()
{
}
