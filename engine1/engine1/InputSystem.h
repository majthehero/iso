#pragma once

#include "main.h"
#include "System.h"

class InputSystem : public System
{
public:
	InputSystem();
	InputSystem(MessageBus *msgBus);
	~InputSystem();

	int update();

private:
	ALLEGRO_KEYBOARD_STATE *kbdState;
	ALLEGRO_MOUSE_STATE *mouseState;
	int mouseClickLength = 0;

};