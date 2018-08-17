# include "Trap.h"

void render(Camera* camP)
{
	ScreenPosition position_screen;

	position_screen = camP->camera2dTransform(&this->world_position);

	al_draw_bitmap(this->spriteP, position_screen.x, position_screen.y, NULL);
}