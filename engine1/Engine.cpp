#include "Engine.h"

#include "System.h"
#include "World.h"

Engine::Engine()
{
}


Engine::~Engine()
{
}





int main()
{
	// init allegro

	al_init();
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
	World world;
	gameSystem.assignWorld(&world);
	renderSystem.assignWorld(&world);
	
	// game loop
	while (true)
	{
		inputSystem.update();
		gameSystem.update();
		renderSystem.update();
	}

	return 0;
}
