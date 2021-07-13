#pragma once

#include <unordered_map>
#include "Communicator.h"
#include "ECS_Types.h"

using Subscriptions = std::unordered_map<EntityMessage, Communicator>;

class MessageHandler
{
public:
	bool subscribe(const EntityMessage& msgType, Observer* observer);
	bool unSubscribe(const EntityMessage& msgType, Observer* observer);
	void dispatch(const Message& msg);

private:
	Subscriptions communicators;
};