#include "InputSystem.h"



InputSystem::InputSystem()
{
	msgBus = NULL;
	al_install_keyboard();
	al_install_mouse();
	kbdState = (ALLEGRO_KEYBOARD_STATE*)malloc(sizeof(ALLEGRO_KEYBOARD_STATE));
	mouseState = (ALLEGRO_MOUSE_STATE*)malloc(sizeof(ALLEGRO_MOUSE_STATE));
}

InputSystem::InputSystem(MessageBus* msgBus)
{
	this->msgBus = msgBus;
	al_install_keyboard();
	al_install_mouse();
	kbdState = (ALLEGRO_KEYBOARD_STATE*)malloc(sizeof(ALLEGRO_KEYBOARD_STATE));
	mouseState = (ALLEGRO_MOUSE_STATE*)malloc(sizeof(ALLEGRO_MOUSE_STATE));
}

InputSystem::~InputSystem()
{
	free(kbdState);
	free(mouseState);
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

int InputSystem::update()
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
	return 0;
}
