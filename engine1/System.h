#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "Messaging.h"


class System
{
protected:
	MessageBus messages;
public:
	System();
	~System();

	virtual void update() = 0;

};

class InputSystem : public System
{
public:
	InputSystem(MessageBus msgBus);
	~InputSystem();

	// Inherited via System
	virtual void update() override;
};

class GameSystem : public System
{
public:
	GameSystem(MessageBus msgBus);
	~GameSystem();

	// Inherited via System
	virtual void update() override;
};

class RenderSystem : public System
{
public:
	RenderSystem(MessageBus msgBus);
	~RenderSystem();

	// Inherited via System
	virtual void update() override;
};

