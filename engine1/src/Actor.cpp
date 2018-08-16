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

void Actor::setSprite(ALLEGRO_BITMAP* spriteP)
{
	this->spriteP = spriteP;
}

Actor::~Actor()
{
}

void Actor::update(float deltaT)
{
	// gravity
	this->momentum_y += 0.1 * deltaT;

	printf("Update: moment: %f %f\n", this->momentum_x, this->momentum_y);
	printf("Update: position: %f %f\n", this->world_position.x, this->world_position.y);
	this->world_position.x += this->momentum_x * deltaT;
	this->world_position.y += this->momentum_y * deltaT;

	this->camera.setPosition(this->world_position.x,
		this->world_position.y);
}