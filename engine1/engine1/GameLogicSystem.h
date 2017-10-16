#pragma once

#include "main.h"
#include "System.h"

class GameLogicSystem : public System
{
public:
	GameLogicSystem();
	GameLogicSystem(MessageBus* msgBus);
	~GameLogicSystem();

	int update();

private:
	int cock;

};