#pragma once

#include "Actor.h"
#include "Camera.h"


Actor::Actor()
{
	this->camera = Camera();
	this->camera.setScale(1.0);
	this->camera.setPosition(this->world_position.x,
							 this->world_position.y);

}


Actor::~Actor()
{
}
