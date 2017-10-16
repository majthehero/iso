#pragma once

#include "Message.h"

class MessageBus
{
public:
	MessageBus();
	MessageBus(int size);

	void post(Message msg);
	
	Message* access();
	int getSize();

private:
	Message* messages;
	int size = 0;
};