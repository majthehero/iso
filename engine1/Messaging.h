#pragma once

#include <vector>

enum SYSTEM {
	SYS_MSGBUS = 0,
	SYS_INPUT,
	SYS_GAME,
	SYS_RENDER,

	SYS_ERROR
};

enum COMMAND {
	// input sends:
	// kbd
	CMD_UP,
	CMD_RIGHT,
	CMD_DOWN,
	CMD_LEFT,
	CMD_ACTION,
	// mouse
	CMD_LCLICK,
	CMD_RCLICK,
	// game sends:
	CMD_RENDER,

	CMD_ERROR
};


class Message
{
private:
	SYSTEM dest;
	COMMAND command;
	bool remove;
public:
	Message();
	~Message();

	void mark_remove();
	void setDest(SYSTEM destSys);
	SYSTEM getDest();
	void setComm(COMMAND comm);
	COMMAND getCommand();
	bool shouldRemove();

};

class MessageBus
{
private:
	std::vector<Message> messages;
public:
	MessageBus();
	~MessageBus();

	void post(Message msg);
	void removeMarked();
	std::vector<Message>::iterator getIterator();
	std::vector<Message>::iterator iteratorEnd();
};

