#include "SystemManager.h"

SystemManager::SystemManager() : entityMgr(nullptr)
{
	//systems[SystemType::Phyics] = new Physics(this, SystemType::Phyics);
}

SystemManager::~SystemManager()
{
	purgeSystems();
}

void SystemManager::setEntityManager(EntityManager* entityMgr)
{
	if(!this->entityMgr)
		this->entityMgr = entityMgr;
}

void SystemManager::entityModified(const EntityId& entityId, const BitMask& mask)
{
	for (auto& system : systems)
	{
		System* sys = system.second;
		if (sys->fitsRequirement(mask))
		{
			if (!sys->hasEntity(entityId))
				sys->addEntity(entityId);
		}
		else
		{
			if (sys->hasEntity(entityId))
				sys->removeEntity(entityId);
		}
	}
}

void SystemManager::addEvent(const EntityId& entityId, const EventID& event)
{
	events[entityId].addEvent(event);
}

void SystemManager::removeEntity(unsigned int entity)
{
	for (auto& system : systems)
	{
		system.second->removeEntity(entity);
	}
}

void SystemManager::purgeEntities()
{
	for (auto& system : systems)
	{
		system.second->purge();
	}
}

void SystemManager::update(float dt)
{
	for (auto& system : systems)
	{
		system.second->update(dt);
	}
	handleEvents();
}

void SystemManager::handleEvents()
{
	for (auto event : events)
	{
		EventID id = 0;
		while (event.second.processEvents(id))
		{
			for (auto system : systems)
			{
				if (system.second->hasEntity(event.first))
				{
					system.second->handleEvent(event.first, EntityEvent(id));
				}
			}
		}
	}
}

void SystemManager::purgeSystems()
{
	for (auto& system : systems)
	{
		delete system.second;
	}
	systems.clear();
}
