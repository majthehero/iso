#include "System.h"



System::System()
{
}


System::~System()
{
}


InputSystem::InputSystem(MessageBus& msgBus)
{
	messages = msgBus;
	eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
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
	msg.setDest(SYS_INPUT);
	// read input events
	while (al_get_next_event(eventQueue, &event)) 
	{
		if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (event.keyboard.unichar == key_lut.key_down) {
				msg.setComm(CMD_DOWN);
			} 
			else if (event.keyboard.unichar == key_lut.key_up) {
				msg.setComm(CMD_UP);
			}
			else if (event.keyboard.unichar == key_lut.key_left) {
				msg.setComm(CMD_LEFT);
			}
			else if (event.keyboard.unichar == key_lut.key_right) {
				msg.setComm(CMD_RIGHT);
			}
			else if (event.keyboard.unichar == key_lut.key_action) {
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
		messages.post(msg);
	}
}


GameSystem::GameSystem(MessageBus& msgBus)
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

	// read messages
	auto iBegin = messages.getIterator();
	auto iEnd = messages.iteratorEnd();
	for (; iBegin != iEnd; iBegin++) {
		if (iBegin->getDest() == SYS_GAME) {
			switch (iBegin->getCommand()) {
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
				messages.post(msg);
				cerr << "click, render request sent\n";
				break;
			case CMD_RCLICK:
				cerr << "right click, fuck you\n";
				break;
			}
		}
		else {
			// message not for me, ignore
			continue;
		}
	}
}


RenderSystem::RenderSystem(MessageBus& msgBus)
{
	messages = msgBus;
	
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update()
{
}
