#include "RenderableObject.h"

RenderableObject::RenderableObject()
{
	ALLEGRO_DISPLAY* displ = al_get_current_display();

	base_font = al_load_font("RobotoCondensed-Light.tff", 16, NULL);
	if (!base_font) std::cerr << "RobotoCondensed-Light.tff load failed" << std::endl;
	backC = al_map_rgb_f(0.0f, 0.1f, 0.3f);
	fontC = al_map_rgb_f(1.0f, 0.8f, 0.3f);


	empty_sprite = al_create_bitmap(64, 64);
	al_set_target_bitmap(empty_sprite);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_set_target_bitmap(al_get_backbuffer(displ));

}


RenderableObject::~RenderableObject()
{
}

void RenderableObject::render(Camera * camP)
{
	std::cerr << "RendObj::render\n";

	// allocate space for position data
	ScreenPosition itemPosSP(0.0f, 0.0f);

	float srcScale = TILE_SIZE;
	float destScale = TILE_SIZE * camP->getScale();

	itemPosSP = camP->camera2dTransform(&worldPosition);

	if (!spriteP || flags.err_sprite) {
		spriteP = empty_sprite;
		flags.err_sprite = true;
	}
	if (flags.render) 
		al_draw_scaled_bitmap(
			spriteP,			// bitmap
			0, 0,				// src xy !todo: animation support
			srcScale, srcScale,	// src scale
			itemPosSP.x,		// dest x
			itemPosSP.y,			//  y
			destScale, destScale,	// dest scale
			NULL);
	//if (flags.devel)
	//	al_draw_text(base_font, );
		
}
