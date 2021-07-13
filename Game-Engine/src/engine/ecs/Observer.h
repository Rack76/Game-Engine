#pragma once

#include "Message.h"

class Observer
{
public:
	virtual ~Observer(){}
	virtual void notify(const Message& msg) = 0;
};