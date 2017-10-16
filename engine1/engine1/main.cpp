#include "main.h"
#include "System.h"
#include "InputSystem.h"
#include "GameLogicSystem.h"
#include "RenderSystem.h"

int main() 
{
	MessageBus* messageBus = new MessageBus();
	GameLogicSystem* gameLogic = new GameLogicSystem(messageBus);
	InputSystem* inputSystem = new InputSystem(messageBus);
	RenderSystem* renderSystem = new RenderSystem(messageBus);

	while (true) 
	{
		inputSystem->update();
		gameLogic->update();
		renderSystem->update();
	}
	
	delete messageBus;

	return 0;
}
