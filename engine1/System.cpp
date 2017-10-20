#include "System.h"

#include "debug.h"


System::System()
{
}


System::~System()
{
}


InputSystem::InputSystem(MessageBus* msgBus)
{
	int err;
	messages = msgBus;
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	// set up mouse lut and keyboard lut
	// !todo: read from ini
	key_lut.key_action = ALLEGRO_KEY_E;
	key_lut.key_down = ALLEGRO_KEY_S;
	key_lut.key_left = ALLEGRO_KEY_A;
	key_lut.key_up = ALLEGRO_KEY_W;
	key_lut.key_right = ALLEGRO_KEY_D;
	mouse_lut.mouseL = 1;
	mouse_lut.mouseR = 3;
	LOG("InputSystem online" );
}


InputSystem::~InputSystem()
{
	al_unregister_event_source(eventQueue, al_get_keyboard_event_source());
	al_unregister_event_source(eventQueue, al_get_mouse_event_source());
	al_destroy_event_queue(eventQueue);
	LOG("InputSystem offline");
}

void InputSystem::update()
{
	// prepare msg
	Message msg;
	msg.setDest(SYS_GAME);
	// read input events
	while (al_get_next_event(eventQueue, &event)) 
	{
		if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
			LOG("input::update::event.key");
			if (event.keyboard.keycode == key_lut.key_down) {
				msg.setComm(CMD_DOWN);
			} 
			else if (event.keyboard.keycode == key_lut.key_up) {
				msg.setComm(CMD_UP);
			}
			else if (event.keyboard.keycode == key_lut.key_left) {
				msg.setComm(CMD_LEFT);
			}
			else if (event.keyboard.keycode == key_lut.key_right) {
				msg.setComm(CMD_RIGHT);
			}
			else if (event.keyboard.keycode == key_lut.key_action) {
				msg.setComm(CMD_ACTION); 
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (event.mouse.button == mouse_lut.mouseL) { 
				msg.setComm(CMD_LCLICK);
			}
			else if (event.mouse.button == mouse_lut.mouseR) {
				msg.setComm(CMD_RCLICK);
			}
		}
		else {
			// event not usable, ignore
			continue;
		}
		// send msg
		messages->post(msg);
	}
}


GameSystem::GameSystem(MessageBus* msgBus)
{
	messages = msgBus;
	LOG("GameSystem online");
}


GameSystem::~GameSystem()
{
	LOG("GameSystem offline");
}

void GameSystem::update()
{
	using namespace std;
	// prepare message
	Message msg;
	messages->temp.clear();

	// read messages
	/*std::vector<Message>::iterator iBegin = messages->getIterator();
	std::vector<Message>::iterator iEnd = messages->iteratorEnd();*/
	std::pair < std::vector<Message>::iterator,
		std::vector<Message>::iterator> p = messages->getIterators();
	for (; p.first != p.second; p.first++) {
		if (p.first->getDest() == SYS_GAME) {
			switch (p.first->getCommand()) {
			case CMD_UP:
				cerr << "_^_\n";
				break;
			case CMD_DOWN:
				cerr << "-v-\n";
				break;
			case CMD_LEFT:
				cerr << "<--\n";
				break;
			case CMD_RIGHT:
				cerr << "-->\n";
				break;
			case CMD_LCLICK:
				msg.setDest(SYS_RENDER);
				msg.setComm(CMD_RENDER);
				messages->temp.push_back(msg);
				cerr << "click, render request prepared\n";
				break;
			case CMD_RCLICK:
				cerr << "right click, fuck you\n";
				break;
			}
			p.first->mark_remove();
		}
		else {
			// message not for me, ignore
			continue;
		}
	}
	// send messages
	for (auto m : messages->temp) {
		messages->post(m); // !todo: messagebus::post should do this
	}
	messages->temp.clear();
}


RenderSystem::RenderSystem(MessageBus* msgBus)
{
	messages = msgBus;
	width = 960;
	height = 540;
	display = al_create_display(width, height);
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::render() // !todo after resolving World::render()
							// this function needs only call all Renderable::render()
{
	Position pos{ 0,0 };
	/*std::pair<std::array<WorldTile, MAP_SIZE>::iterator,
		std::array<WorldTile, MAP_SIZE>::iterator> p = world->getMap().getMapIterators();*/
	// !slow: this should use iterators to get tiles faster
	auto& assets = world->getMap().getAssets();
	/*for (; p.first != p.second; p.first++)
	{*/
	int i, j;
	for (i = 0, pos.y = 0; pos.y < DEBUG_HEIGHT; i++, pos.y += TILE_SIZE)
	{
		for (j = 0, pos.x = 0; pos.x < DEBUG_WIDTH; j++, pos.x += TILE_SIZE)
		{
			WorldTile wt = world->getMap().getTile(j, i);
			al_draw_bitmap(
				assets.at(wt.type),
				pos.x,
				pos.y,
				NULL);
		}
	}

	al_flip_display(); // must be called at the end of render step
}

void RenderSystem::update()
{
	auto iBegin = messages->getIterator();
	auto iEnd = messages->iteratorEnd();
	for ( ; iBegin != iEnd; iBegin++) 
	{
		if (iBegin->getDest() == SYS_RENDER) 
		{
			if (iBegin->getCommand() == CMD_RENDER) 
			{
				render();
			}
			else 
			{
				std::cerr << "lol wut" << std::endl;
			}
		}
	}
}
