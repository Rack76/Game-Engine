#pragma once

#include <vector>
#include "ECS_Types.h"
#include "Observer.h"
#include "BitMask.h"
#include "SystemManager.h"

class Component;

using EntityId = unsigned int;
using EntityList = std::vector<EntityId>;
using Requirements = std::vector<BitMask>;

class System : public Observer
{
public:
	System(SystemManager* sysMgr, const SystemType& systemType);
	~System();

	Component* getComponent(const EntityId& entity, const ComponentType& component);
	bool addEntity(const EntityId& entity);
	bool hasEntity(const EntityId& entity);
	bool removeEntity(const EntityId& entity);
	void addRequiredEntityTypes(const BitMask& mask);

	SystemType getId() { return sysType; }

	template <class T>
	T* getComponent(const EntityId& entity, const ComponentType& componentType)
	{
		return sysMgr->getEntityMgr()->getComponent<T>(entity, componentType);
	}

	bool fitsRequirement(const BitMask& bits);
	void purge();

	virtual void update(float dt) = 0;
	virtual void handleEvent(const EntityId& entity, const EntityEvent& event) = 0;

protected:
	SystemType sysType;
	Requirements requiredEntityTypes;
	EntityList entityList;

	SystemManager* sysMgr;
};