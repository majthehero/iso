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

void Actor::setSprite(ALLEGRO_BITMAP* spriteP)
{
	this->spriteP = spriteP;
}

// object

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

// renderble

void Actor::render(Camera* camP)
{
	float srcScale = TILE_SIZE;
	float destScale = TILE_SIZE * camP->getScale();

	float ws_pos_x = this->world_position.x;
	float ws_pos_y = this->world_position.y;
	ScreenPosition itemPosSP = camP->camera2dTransform(&WorldPosition(ws_pos_x, ws_pos_y));

	if (flags.render)
		al_draw_scaled_bitmap(
			this->spriteP,		// bitmap
			0, 0,					// src xy
			srcScale, srcScale,		// src scale
			itemPosSP.x,		// dest x
			itemPosSP.y,			//  y
			destScale, destScale,	// dest scale
			NULL);

	if (flags.devel) {
		char coords_str[20];
		sprintf_s(coords_str, 12, "Actor
: %d,%d ", (int)ws_pos_x, (int)ws_pos_y);
		if (!coords_str) sprintf_s(coords_str, 20, "err");
		al_draw_text(base_font, fontC,
			itemPosSP.x,		// dest x
			itemPosSP.y,			//  y
			NULL,				// flags
			coords_str);		// text c string
	}
}

// collider
bool Actor::collide(Collider* col)
{
	// note: actor collides by setting directional collision to self - to update self correctly
	
	// check if not collision
	if (this->boundingBox.max_x < col->boundingBox.min_x 
		this->boundingBox.min_x > col->boundingBox.max_x 
}

// effector

