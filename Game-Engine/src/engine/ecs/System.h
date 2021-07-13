#pragma once

#include <vector>
#include "ECS_Types.h"
#include "Observer.h"
#include "BitMask.h"

class SystemManager;

using EntityId = unsigned int;
using EntityList = std::vector<EntityId>;
using Requirements = std::vector<BitMask>;

class System : public Observer
{
public:
	System(SystemManager* sysMgr, const SystemType& systemType);
	~System();

	bool addEntity(const EntityId& entity);
	bool hasEntity(const EntityId& entity);
	bool removeEntity(const EntityId& entity);

	SystemType getId() { return sysType; }

	bool fitsRequirement(const BitMask& bits);
	void purge();

	virtual void update(float dt) = 0;
	virtual void handleEvent(const EntityId& entity, const EntityEvent& event) = 0;

protected:
	SystemType sysType;
	Requirements requiredComponents;
	EntityList entityList;

	SystemManager* sysMgr;
};