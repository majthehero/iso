#pragma once

#include <stdlib.h>
#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\keyboard.h>
#include <allegro5\mouse.h>

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

int main();
