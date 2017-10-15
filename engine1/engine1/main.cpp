#include <stdlib.h>
#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\keyboard.h>
#include <allegro5\mouse.h>


int main() 
{
	MessageBus* messageBus = new MessageBus();
	InputSystem* inputSystem = new InputSystem();
	GameLogicSystem* gameLogic = new GameLogicSystem();

	delete messageBus;

	return 0;
}


class System
{
protected:
	MessageBus *msgBus;
	
public:
	int broadcastMsg(Message msg)
	{
		msgBus->post(msg);
	}

	Message* readMsg()
	{
		msgBus->access();
	}

	virtual int update() {}

};

class Message
{
public:
	int command;
	int destSystem;
};

enum SYSTEM {
	SYS_INPUT,
	SYS_GAMELOGIC,
	SYS_RENDER
};

enum COMMAND {
	CMD_UP,
	CMD_RIGHT,
	CMD_DOWN,
	CMD_LEFT,
	CMD_CAST,
	CMD_MELEE,
	CMD_CLICK,
	CMD_PRESSED
};

class MessageBus
{
public:
	MessageBus() 
	{
		this->size = 0;
		messages = (Message*)calloc(16, sizeof(Message));
	}
	MessageBus(int size) 
	{
		this->size = 0;
		messages = (Message*)calloc(size, sizeof(Message));
	}

	void post(Message msg) 
	{
		messages[this->size] = msg;
		this->size++;
	}
	Message* access()
	{
		return messages;
	} 
	int getSize()
	{
		return size;
	}

private:
	Message* messages;
	int size;
};

class InputSystem : public System 
{
public:
	InputSystem() 
	{
		al_install_keyboard();
		al_install_mouse();
		kbdState = (ALLEGRO_KEYBOARD_STATE*)malloc(sizeof(ALLEGRO_KEYBOARD_STATE));
		mouseState = (ALLEGRO_MOUSE_STATE*)malloc(sizeof(ALLEGRO_MOUSE_STATE));
	}
	~InputSystem() 
	{
		free(kbdState);
		free(mouseState);
		al_uninstall_keyboard();
		al_uninstall_mouse();
	}

	int update() 
	{
		al_get_keyboard_state(kbdState);
		al_get_mouse_state(mouseState);

		if (al_key_down(kbdState, ALLEGRO_KEY_W)) // todo solve this piece of shit
		{
			Message msg;
			msg.destSystem = SYS_GAMELOGIC;
			msg.command = CMD_UP;
			broadcastMsg(msg);
		}
		else if (al_key_down(kbdState, ALLEGRO_KEY_D)) 
		{
			Message msg;
			msg.destSystem = SYS_GAMELOGIC;
			msg.command = CMD_RIGHT;
			broadcastMsg(msg);
		}
		else if (al_key_down(kbdState, ALLEGRO_KEY_S))
		{
			Message msg;
			msg.destSystem = SYS_GAMELOGIC;
			msg.command = CMD_DOWN;
			broadcastMsg(msg);
		}
		else if (al_key_down(kbdState, ALLEGRO_KEY_A))
		{
			Message msg;
			msg.destSystem = SYS_GAMELOGIC;
			msg.command = CMD_LEFT;
			broadcastMsg(msg);
		}

		if (al_mouse_button_down(mouseState, 1)) 
		{
			mouseClickLength++;
		}
		else 
		{
			if (mouseClickLength > 0) 
			{
				// mouse clicked
				if (mouseClickLength > 5) 
				{
					Message msg;
					msg.destSystem = SYS_GAMELOGIC;
					msg.command = CMD_CLICK;
					broadcastMsg(msg);
					mouseClickLength = 0;
				}
				
			}
		}

	}
	

private:
	ALLEGRO_KEYBOARD_STATE *kbdState;
	ALLEGRO_MOUSE_STATE *mouseState;
	int mouseClickLength = 0;

};

class GameLogicSystem : public System
{
public:
	GameLogicSystem()
	{
		;;
	}
	~GameLogicSystem()
	{
		;;
	}

	int update() {
		for (int i = 0; i < msgBus->getSize(); i++) {
			msgBus += 1;//sizeof(Message); // todo which one?
			if (msgBus->access()->destSystem == SYS_GAMELOGIC) {
				if (msgBus->access()->command == CMD_UP) {
					std::cout << "UP!\n";
				}
			}
		}
	}

private:
	int cock;

};