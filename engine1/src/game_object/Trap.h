#include "../RenderableObject.h"

class Trap : 
	public RenderableObject,
	public Collider,
	public GameObject,
	public WORLD_ACCESS
{

public:
	Trap() 
	{
		this->spriteP = this->world.trap_asset;
	}

	Trap(float pos_x, float pos_y) 
	{
		Trap();
		this->world_position.x = pos_x;
		this->world_position.y = pos_y;
		this->sprite_size.first = 64;
		this->sprite_size.second = 64;
		this->sprite_scale.first = 1.0;
		this->sprite_scale.second = 1.0;s
	}

	// renderable object overrides

	void render(Camera* camP) override 
	{
		float srcScale = TILE_SIZE;
		float destScale = TILE_SIZE * camP->getScale();

		itemPos.x = this->world_position.x;
		itemPos.y = this->world_position.y;
		itemPosSP = camP->camera2dTransform(&itemPos);

		if (flags.render)
			al_draw_scaled_bitmap(
				assets.at(wt.type),		// bitmap
				0, 0,					// src xy
				srcScale, srcScale,		// src scale
				itemPosSP.x,		// dest x
				itemPosSP.y,			//  y
				destScale, destScale,	// dest scale
				NULL);

		if (flags.devel) {
			char coords_str[20];
			sprintf_s(coords_str, 20, "%d: %d,%d ", (int)wt.type, (int)itemPos.x, (int)itemPos.y);
			if (!coords_str) sprintf_s(coords_str, 20, "err");
			al_draw_text(base_font, fontC,
				itemPosSP.x,		// dest x
				itemPosSP.y,			//  y
				NULL,				// flags
				coords_str);		// text c string
		}
	}
};