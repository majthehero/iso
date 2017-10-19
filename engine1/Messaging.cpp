#include "Messaging.h"



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

COMMAND Message::getCommand()
{
	if (remove) return CMD_ERROR;
	return command;
}

bool Message::shouldRemove()
{
	return remove;
}


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

std::vector<Message>::iterator MessageBus::iteratorEnd()
{
	return messages.end();
}
