#pragma once
#include "System.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	RenderSystem(MessageBus* msgBus);
	~RenderSystem();

	int Update();

private:
	ALLEGRO_DISPLAY* display;
};

