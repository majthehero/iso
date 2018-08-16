#pragma once

#include <vector>
#include <map>

enum SYSTEM {
	SYS_MSGBUS = 0,
	SYS_INPUT,
	SYS_GAME,
	SYS_RENDER,
	SYS_UI,

	SYS_ERROR
};

enum COMMAND {
	// input sends:
	// kbd
	CMD_FAT_UP,
	CMD_FAT_RIGHT,
	CMD_FAT_DOWN,
	CMD_FAT_LEFT,

	// camera
	CMD_ZOOM_IN,
	CMD_ZOOM_OUT,
	// mouse
	CMD_LCLICK,
	CMD_RCLICK,
	// game sends:
	CMD_RENDER,
	CMD_UI,

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
	std::vector<Message> temp;
	
	MessageBus();
	~MessageBus();

	void post(Message msg);
	void removeMarked();
	std::vector<Message>::iterator getIterator();
	std::pair<std::vector<Message>::iterator,
		std::vector<Message>::iterator> getIterators();
	std::vector<Message>::iterator iteratorEnd();
};

