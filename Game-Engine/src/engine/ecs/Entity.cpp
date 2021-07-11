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
	sysMgr->addEvent(entity, (unsigned int)EntityEvent::Spawned);
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

bool EntityManager::addComponent(const EntityId& entity, const ComponentType& componentType)
{
	auto itr = entityContainer.find(entity);
	if (itr == entityContainer.end())
		return false;

	if (itr->second.first.getBit((unsigned int)componentType))
		return false;

	auto itr2 = componentFactory.find(componentType);

	if (itr2 == componentFactory.end())
		return false;
	
	Component* c = itr2->second();
	itr->second.second.push_back(c);

	itr->second.first.turnBitOn((unsigned int)componentType);

	sysMgr->entityModified(entity, itr->second.first);

	return true;
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
