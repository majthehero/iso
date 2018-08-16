#include "Messaging.h"


// message

Message::Message()
{
	remove = false;
}

Message::~Message()
{
}

void Message::mark_remove()
{
	remove = true;
}

void Message::setDest(SYSTEM destSys)
{
	dest = destSys;
}

SYSTEM Message::getDest()
{
	if (remove) return SYS_ERROR;
	return dest;
}

void Message::setComm(COMMAND comm)
{
	command = comm;
}

COMMAND Message::getCommand()
{
	if (remove) return CMD_ERROR;
	return command;
}

bool Message::shouldRemove()
{
	return remove;
}


// message bus

MessageBus::MessageBus()
{
}

MessageBus::~MessageBus()
{
}

void MessageBus::post(Message msg)
{
	messages.push_back(msg);
}

void MessageBus::removeMarked()
{
	auto previous = getIterator();
	auto removable = previous;

	while (removable != iteratorEnd()) {
		if (removable->shouldRemove()) {
			messages.erase(removable);
			removable = previous;
		}
		removable++;

	}
}

std::vector<Message>::iterator MessageBus::getIterator()
{
	return messages.begin();
}

std::pair<std::vector<Message>::iterator, std::vector<Message>::iterator> MessageBus::getIterators() 
{
	std::pair<std::vector<Message>::iterator, std::vector<Message>::iterator> p;
	p.first = messages.begin();
	p.second = messages.end();

	return p;
}

std::vector<Message>::iterator MessageBus::iteratorEnd()
{
	return messages.end();
}
