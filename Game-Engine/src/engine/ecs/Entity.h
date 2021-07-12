#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <windows.h>
#include <iostream>
#include "Component.h"
#include "BitMask.h"
#include "Components/State2D.h"
#include "SystemManager.h"

using EntityId = unsigned int;

using ComponentContainer = std::vector<Component*>;
using EntityData = std::pair<BitMask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;
using ComponentsAttribInit = std::vector<std::function<void(ComponentType)>>;

using ComponentFactory = std::unordered_map<ComponentType, std::function<Component* (void)>>;

class EntityManager
{
public:
	EntityManager(SystemManager* sysMgr);
	~EntityManager();

	int addEntity(const BitMask& mask);
	int addEntity(const std::string& fileStr);

	bool removeEntity(const EntityId& entity);

	bool addComponent(const EntityId& entity, const ComponentType& componentType);

	template<class T>
	T* getComponent(const EntityId& entity, const ComponentType& componentType)
	{
		auto itr = entityContainer.find(entity);
		if (itr == entityContainer.end())
			return nullptr;

		if (!itr->second.first.getBit((unsigned int)componentType))
			return nullptr;

		auto container = itr->second.second;
		auto component = std::find_if(container.begin(), container.end(),
			[&componentType](Component* c)
			{return c->getType() == componentType; });

		return (component == container.end() ? nullptr : dynamic_cast<T*>(*component));
	}

	bool removeComponent(const EntityId& entity, const ComponentType& componentType);

	bool hasComponent(const EntityId& entity, const ComponentType& componentType);

	void addComponentAttribInit(std::function<void(ComponentType)> func);

	void purge();

private:
	template <class T>
	void addComponentType(const ComponentType& id)
	{
		componentFactory[id] = []() -> Component* {return new T(); };
	}

	ComponentsAttribInit cAtrbInit;
	SystemManager* sysMgr;
	EntityContainer entityContainer;
	ComponentFactory componentFactory;
	unsigned int counter;
};