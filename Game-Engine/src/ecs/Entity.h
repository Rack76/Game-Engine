#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include "Component.h"
#include "BitMask.h"

using EntityId = unsigned int;

using ComponentContainer = std::vector<Component*>;
using EntityData = std::pair<BitMask, ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId, EntityData>;

using ComponentFactory = std::unordered_map<ComponentType, std::function<Component* (void)>>;