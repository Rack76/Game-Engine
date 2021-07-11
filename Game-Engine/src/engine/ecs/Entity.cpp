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

bool EntityManager::removeComponent(const EntityId& entity, const ComponentType& componentType)
{
	auto itr = entityContainer.find(entity);
	if (itr == entityContainer.end())
		return false;

	if (!itr->second.first.getBit((unsigned int)componentType))
		return false;

	auto container = itr->second.second;
	auto component = std::find_if(container.begin(), container.end(), 
		[&componentType](Component* c) {return c->getType() == componentType; });

	if (component == container.end())
		return false;

	delete (*component);
	container.erase(component);

	itr->second.first.clearBit((unsigned int)componentType);

	sysMgr->entityModified(entity, itr->second.first);

	return true;
}

bool EntityManager::hasComponent(const EntityId& entity, const ComponentType& componentType)
{
	auto itr = entityContainer.find(entity);
	if (itr == entityContainer.end())
		return false;

	auto bitmask = itr->second.first;
	return bitmask.getBit((unsigned int)componentType);
}

void EntityManager::purge()
{
	sysMgr->purgeEntities();
	for (auto entity : entityContainer)
	{
		for (auto component : entity.second.second)
		{
			delete component;
		}
		entity.second.second.clear();
		entity.second.first.clear();
	}
	entityContainer.clear();
}
