#include "System.h"



System::System()
{
}


System::~System()
{
}


InputSystem::InputSystem(MessageBus msgBus)
{
	messages = msgBus;
}


InputSystem::~InputSystem()
{
}

void InputSystem::update()
{

}


GameSystem::GameSystem(MessageBus msgBus)
{
	messages = msgBus;
}


GameSystem::~GameSystem()
{
}

void GameSystem::update()
{
}


RenderSystem::RenderSystem(MessageBus msgBus)
{
	messages = msgBus;
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update()
{
}
