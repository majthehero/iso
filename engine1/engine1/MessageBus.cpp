#include "main.h"
#include "MessageBus.h"

MessageBus::MessageBus()
{
	this->size = 0;
	messages = (Message*)calloc(16, sizeof(Message));
}

MessageBus::MessageBus(int size)
{
	this->size = 0;
	messages = (Message*)calloc(size, sizeof(Message));
}

void MessageBus::post(Message msg)
{
	messages[this->size] = msg;
	this->size++;
}

Message * MessageBus::access()
{
	return messages;
}

int MessageBus::getSize()
{
	return this->size;
}
