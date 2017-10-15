#pragma once

#include "Message.h"

class MessageBus
{
public:
	MessageBus();
	~MessageBus();

	int postMessage();
	int readMessage();

private:
	Message msgStack[];
};

