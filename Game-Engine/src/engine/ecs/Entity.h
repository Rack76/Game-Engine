#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include "Component.h"
#include "BitMask.h"
#include "Components/State2D.h"
#include "SystemManager.h"

using EntityId = unsigned int;

using ComponentContainer = std::vector<Component*>;
using EntityData = std::pair<BitMask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;

using ComponentFactory = std::unordered_map<ComponentType, std::function<Component* (void)>>;

class EntityManager
{
public:
	EntityManager(SystemManager* sysMgr);
	~EntityManager();

	void addEntity(const BitMask& mask);
	void addEntity(const std::string& fileStr);

	bool removeEntity(const EntityId& entity);

	bool addComponent(const EntityId& entity, const ComponentType& componentType);

	template<class T>
	T* getComponent(const EntityId& entity, const ComponentType& componentType)
	{
		auto itr = entityContainer.find(entity);
		if (itr == entityContainer.end())
			return nullptr;

		if (!itr->first.getBit(componentType))
			return nullptr;

		auto container = itr->second.second;
		auto component = std::find_if(container->begin(), container->end(),
			[&componentType](Component* c)
			{return c->getType() == componentType; });

		return (component == container.end() ? nullptr : dynamic_cast<T*>(*component));
	}

	void removeComponent(const EntityId& entity, const ComponentType& componentType);

	bool hasComponent(const EntityId& entity, const ComponentType& componentType);

	void purge();

private:
	template <class T>
	void addComponentType(const ComponentType& id)
	{
		componentFactory[id] = []() -> Component* {return new T(); };
	}

	SystemManager* sysMgr;
	EntityContainer entityContainer;
	ComponentFactory componentFactory;
	unsigned int counter;
};