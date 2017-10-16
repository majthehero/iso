#include "System.h"

System::System() {}

System::System(MessageBus * msgBus)
{
	this->msgBus = msgBus;
}

int System::broadcastMsg(Message msg)
{
	msgBus->post(msg);
	return 0;
}

Message * System::readMsg()
{
	return msgBus->access();
}

int System::update()
{
	return 1;
}
