#include "System.h"


System::System()
{
}


System::~System()
{
}

void System::setMessageBus(MessageBus * msgBusP)
{
	messages = msgBusP;
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

}


InputSystem::~InputSystem()
{
	al_unregister_event_source(eventQueue, al_get_keyboard_event_source());
	al_unregister_event_source(eventQueue, al_get_mouse_event_source());
	al_destroy_event_queue(eventQueue);

}

void InputSystem::update(float deltaT)
{
	// prepare msg
	Message msg;
	msg.setDest(SYS_GAME);
	// read input events
	while (al_get_next_event(eventQueue, &event))
	{
		if (event.type == ALLEGRO_EVENT_KEY_CHAR) {

			if (event.keyboard.keycode == key_lut.key_down) {
				msg.setComm(CMD_FAT_DOWN);
			}
			else if (event.keyboard.keycode == key_lut.key_up) {
				msg.setComm(CMD_FAT_UP);
			}
			else if (event.keyboard.keycode == key_lut.key_left) {
				msg.setComm(CMD_FAT_LEFT);
			}
			else if (event.keyboard.keycode == key_lut.key_right) {
				msg.setComm(CMD_FAT_RIGHT);
			}
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			if (event.mouse.button == mouse_lut.mouseL) {
				msg.setComm(CMD_ZOOM_IN);
			}
			else if (event.mouse.button == mouse_lut.mouseR) {
				msg.setComm(CMD_ZOOM_OUT);
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

}


GameSystem::~GameSystem()
{

}

void GameSystem::update(float deltaT)
{
	using namespace std;
	// prepare message
	Message msg;
	messages->temp.clear();
	WorldPosition move;

	// read messages
	std::pair <std::vector<Message>::iterator,
		std::vector<Message>::iterator> p = messages->getIterators();

	for (; p.first != p.second; p.first++) {

		if (p.first->shouldRemove()) continue;

		if (p.first->getDest() == SYS_GAME) {
			switch (p.first->getCommand()) {
			
			// FAT PLAYER MOVEMENT
			case CMD_FAT_LEFT:
				world->fat.moveLeft();
				break;

			case CMD_FAT_DOWN:
				world->fat.roll();
				break;

			case CMD_FAT_RIGHT:
				world->fat.moveRight();
				break;

			case CMD_FAT_UP:
				world->fat.jump();
				break;

			// SLIM PLAYER MOVEMENT

			// camera control
			case CMD_ZOOM_IN:
				world->getCamera()->setScale(
					world->getCamera()->getScale() / 0.8); 
				break;
			
			case CMD_ZOOM_OUT:
				world->getCamera()->setScale(
					world->getCamera()->getScale() * 0.8);
				break;
			}

			p.first->mark_remove();
		}
	}
	// send render command
	msg.setDest(SYS_RENDER);
	msg.setComm(CMD_RENDER);
	messages->temp.push_back(msg);
	msg.setDest(SYS_UI);
	msg.setComm(CMD_UI);
	messages->temp.push_back(msg);

	// send messages
	for (auto m : messages->temp) {
		messages->post(m); 
	}
	messages->temp.clear();
}
