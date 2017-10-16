#include "RenderSystem.h"



RenderSystem::RenderSystem()
{
}

RenderSystem::RenderSystem(MessageBus * msgBus)
{
	display = al_create_display(800, 600); // todo hardcoded display size

}


RenderSystem::~RenderSystem()
{
	al_destroy_display(display);
}

int RenderSystem::Update() {
	ALLEGRO_COLOR bgColor;
	bgColor.a = 1.0;
	bgColor.r = 0.4;
	bgColor.g = 1.0;
	bgColor.b = 0.8;
	al_clear_to_color(bgColor);

	return 0;
}