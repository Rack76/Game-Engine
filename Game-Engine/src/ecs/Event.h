#pragma once

#include <queue>

using EventID = unsigned int;

class EventQueue
{
public:
	void addEvent(const EventID& event);

	bool processEvents(EventID& event);

	void clear();

private:
	std::queue<EventID> queue;
};