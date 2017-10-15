#pragma once

#include "allegro5\allegro.h"
#include "allegro5\keyboard.h"
#include "allegro5\mouse.h"


class Input
{
public:
	Input();
	~Input();

	int update();

	int post();
	int read();

private:
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_MOUSE_STATE mouseState;

};

