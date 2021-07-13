#pragma once

#include <vector>
#include "Observer.h"

using ObserverContainer = std::vector<Observer*>;

class Communicator
{
public:
	bool addObserver(Observer* observer);
	bool removeObserver(Observer* observer);
	bool hasObserver(Observer* observer);
	void broadcast(const Message& msg);

private:
	ObserverContainer observers;
};