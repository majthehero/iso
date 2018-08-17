#pragma once

#include "Exit.h"

Exit::Exit()
{
	this->spriteP = world->exit_asset;
}

// object
void Exit::update(float deltaT)
{
	;;
}

// rendarable
void Exit::render(Camera* camP)
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
		sprintf_s(coords_str, 12, "Trap: %d,%d ", (int)ws_pos_x, (int)ws_pos_y);
		if (!coords_str) sprintf_s(coords_str, 20, "err");
		al_draw_text(base_font, fontC,
			itemPosSP.x,		// dest x
			itemPosSP.y,			//  y
			NULL,				// flags
			coords_str);		// text c string
	}
}

// collider

// effector