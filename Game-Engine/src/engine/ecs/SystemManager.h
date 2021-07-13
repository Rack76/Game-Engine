#pragma once

#include <unordered_map>
#include "BitMask.h"
#include "System.h"
#include "Event.h"
#include "MessageHandler.h"
#include "Entity.h"

using SystemContainer = std::unordered_map<SystemType, System*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void setEntityManager(EntityManager* entityMgr);
	void entityModified(const EntityId& entityId, const BitMask& mask);
	void addEvent(const EntityId& entityId, const EventID& event);
	void removeEntity(unsigned int entity);
	void purgeEntities();

	template <class T>
	T* getSystem(const SystemType& sysType)
	{
		auto itr = systems.find(sysType);

		return (itr != system.end() ? dynamic_cast<T*>(itr->second) : nullptr);
	}

	void update(float dt);
	void handleEvents();
	void purgeSystems();

private:
	SystemContainer systems;
	EntityManager* entityMgr;
	EntityEventContainer events;
	MessageHandler msgHandler;
};