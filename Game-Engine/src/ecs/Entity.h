#pragma once

#include <vector>
#include <map>
#include "Component.h"
#include "BitMask.h"

using EntityId = unsigned int;

using ComponentContainer = std::vector<Component*>;
using EntityData = std::pair<BitMask, ComponentContainer>;
using EntityContainer = std::map<EntityId, EntityData>;

