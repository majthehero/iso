#include "GameLogicSystem.h"

GameLogicSystem::GameLogicSystem()
{
	al_init();
}

GameLogicSystem::GameLogicSystem(MessageBus * msgBus)
{
	al_init();
	this->msgBus = msgBus;
}

GameLogicSystem::~GameLogicSystem()
{
	al_uninstall_system();
}

int GameLogicSystem::update() {
	for (int i = 0; i < msgBus->getSize(); i++) {
		if (msgBus->access()->destSystem == SYS_GAMELOGIC) {
			switch (msgBus->access()->command)
			{
			case CMD_UP:
				std::cout << "UP!\n";
				break;
			case CMD_RIGHT:
				std::cout << "RIGHT!\n";
				break;
			case CMD_LEFT:
				std::cout << "LEFT!\n";
				break;
			case CMD_DOWN:
				std::cout << "DOWN!\n";
				break;
			case CMD_CLICK:
				std::cout << "CLICK!\n";
				break;
			case CMD_PRESSED:
				std::cout << "PRESSED!\n";
				break;

			default:
				break;
			}
		}
		msgBus += sizeof(Message); // todo which one?
	}
	return 0;
}
