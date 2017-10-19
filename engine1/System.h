#pragma once

#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "Messaging.h"
#include "World.h"


class System
{
protected:
	MessageBus messages;
public:
	System();
	~System();

	virtual void update() = 0;
};

/* INPUT SYSTEM */
typedef struct {
	int key_up;		// allegro returns utf-8 codepoints as int
	int key_left;	// see event.keyboard.unichar
	int key_right;
	int key_down;
	int key_action;
} KEY_LUT;

typedef struct {
	int mouseL;		// allegro counts mouse buttons 1 .. n
	int mouseM;		// when check for pressed in ALLEGRO_MOUSE_STATE use 2^(mb_num-1)
	int mouseR;
	int mouse4;
	int mouse5;
} MOUSE_LUT;

class InputSystem 
	: public System
{
private:
	KEY_LUT key_lut;
	MOUSE_LUT mouse_lut;
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* eventQueue;
public:
	InputSystem(MessageBus& msgBus);
	~InputSystem();

	// Inherited via System
	virtual void update() override;
};


/* GAME SYSTEM */
// allowed to write to WORLD_ACCESS
class GameSystem : public System, public WORLD_ACCESS
{
public:
	GameSystem(MessageBus& msgBus);
	~GameSystem();

	// Inherited via System
	virtual void update() override;
};


/* RENDER SYSTEM */
// WORLD_ACCESS should be used read only until write access is locked
class RenderSystem : public System, public WORLD_ACCESS
{
public:
	RenderSystem(MessageBus& msgBus);
	~RenderSystem();

	// Inherited via System
	virtual void update() override;
};

