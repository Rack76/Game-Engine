#include "Communicator.h"

bool Communicator::addObserver(Observer* observer)
{
	if (hasObserver(observer))
		return false;

	observers.push_back(observer);
	return true;
}

bool Communicator::removeObserver(Observer* observer)
{
	auto itr = std::find_if(observers.begin(), observers.end(),
		[&observer](Observer* o) {return observer == o; });

	if (itr == observers.end())
		return false;

	observers.erase(itr);
	return true;
}

bool Communicator::hasObserver(Observer* observer)
{
	auto itr = std::find_if(observers.begin(), observers.end(), 
		[&observer](Observer* o) {return observer == o; });
	return itr != observers.end();
}

void Communicator::broadcast(const Message& msg)
{
	for (auto& observer : observers)
	{
		observer->notify(msg);
	}
}