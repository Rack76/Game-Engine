#include "Event.h"

void EventQueue::addEvent(const EventID& event)
{
	queue.push(event);
}

bool EventQueue::processEvents(EventID& event)
{
	if (queue.empty())
		return false;

	event = queue.front();
	queue.pop();

	return true;
}

void EventQueue::clear()
{
	while (!queue.empty())
	{
		queue.pop();
	}
}
