#include "main.h"

#include "System.h"
#include "RenderSystem.h"
#include "World.h"

double getDeltaTime() {
	double currentTime = al_get_time();
	double deltaTime = currentTime - previous_time;
	frames_per_second = (int) (1.0 / deltaTime);
	previous_time = currentTime;

	return deltaTime;
}

int main()
{
	// init allegro

	al_init();
	previous_time = al_get_time();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
		
	// set up messaging and memory
	MessageBus messageBus;
	// load systems
	InputSystem inputSystem(&messageBus);
	GameSystem gameSystem(&messageBus);
	// render system inits allegro
	RenderSystem renderSystem(&messageBus);
	// world needs allegro to construct itself
	Environment world;
	gameSystem.assignWorld(&world);
	renderSystem.assignWorld(&world);
		
	// game loop
	while (true)
	{
		deltaT = getDeltaTime();
		inputSystem.update(deltaT);
		gameSystem.update(deltaT);
		renderSystem.update(deltaT);
		
	}

	return 0;
}
