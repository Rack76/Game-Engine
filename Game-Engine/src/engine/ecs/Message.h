#pragma once

using MessageType = unsigned int;

struct Message
{
	Message(const MessageType& msgType) : msgType(msgType)
	{}

	MessageType msgType;
	int sender;
	int receiver;

	union
	{

	};
};