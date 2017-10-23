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

void InputSystem::update()
{
	// prepare msg
	Message msg;
	msg.setDest(SYS_GAME);
	// read input events
	while (al_get_next_event(eventQueue, &event))
	{
		if (event.type == ALLEGRO_EVENT_KEY_CHAR) {

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

}


GameSystem::~GameSystem()
{

}

void GameSystem::update()
{
	using namespace std;
	// prepare message
	Message msg;
	messages->temp.clear();
	WorldPosition move;

	// read messages
	std::pair < std::vector<Message>::iterator,
		std::vector<Message>::iterator> p = messages->getIterators();
	for (; p.first != p.second; p.first++) {
		if (p.first->shouldRemove()) continue;
		if (p.first->getDest() == SYS_GAME) {
			switch (p.first->getCommand()) {
			case CMD_UP:
				cerr << "move_camera_^_\n";
				move.x = 0;
				move.y = -0.333;
				world->getCamera()->move(move);
				break;
			case CMD_DOWN:
				cerr << "move_camera-v-\n";
				move.x = 0;
				move.y = 0.333;
				world->getCamera()->move(move);
				break;
			case CMD_LEFT:
				cerr << "move_camera<--\n";
				move.x = -0.333;
				move.y = 0;
				world->getCamera()->move(move);
				break;
			case CMD_RIGHT:
				cerr << "move_camera-->\n";
				move.x = 0.333;
				move.y = 0;
				world->getCamera()->move(move);
				break;
			case CMD_ACTION:
				cerr << "action, zoom in\n";
				world->getCamera()->setScale(
					world->getCamera()->getScale() + 0.333);
				break;
			case CMD_LCLICK:
				msg.setDest(SYS_RENDER);
				msg.setComm(CMD_RENDER);
				messages->temp.push_back(msg);
				cerr << "click, render request prepared\n";
				msg.setDest(SYS_UI);
				msg.setComm(CMD_UI);
				messages->temp.push_back(msg);
				cerr << "click, UI will render\n";
				break;
			case CMD_RCLICK:
				cerr << "right click, zoom out\n";
				world->getCamera()->setScale(
					world->getCamera()->getScale() - 0.333);
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
