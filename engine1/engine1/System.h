#pragma once

#include "Message.h"
#include "MessageBus.h"

class System
{
protected:
	MessageBus *msgBus;

public:
	System();

	System(MessageBus* msgBus);

	int broadcastMsg(Message msg);

	Message* readMsg();

	virtual int update();

};