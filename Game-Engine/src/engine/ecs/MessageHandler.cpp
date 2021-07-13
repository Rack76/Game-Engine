#include "MessageHandler.h"

bool MessageHandler::subscribe(const EntityMessage& msgType, Observer* observer)
{
	return communicators[msgType].addObserver(observer);
}

bool MessageHandler::unSubscribe(const EntityMessage& msgType, Observer* observer)
{
	return communicators[msgType].removeObserver(observer);
}

void MessageHandler::dispatch(const Message& msg)
{
	auto itr = communicators.find((EntityMessage)msg.msgType);
	if (itr == communicators.end())
		return;

	itr->second.broadcast(msg);
}
