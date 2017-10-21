#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\color.h>

#include "Camera.h"

class RenderableObject
{
private:
	static ALLEGRO_BITMAP* empty_sprite;
	static ALLEGRO_FONT* base_font;
	static ALLEGRO_COLOR* white;
	static ALLEGRO_COLOR* black;
	static ALLEGRO_COLOR* red;
	static ALLEGRO_COLOR* green;
	static ALLEGRO_COLOR* blue;
	
	typedef struct {
		bool render;
		bool devel; // will render id on object
		bool error;
		bool err_sprite;
	} Flags;

	Flags flags;


	WorldPosition worldPosition;
	ALLEGRO_BITMAP* spriteP;
	std::pair<int, int> sprite_size; // asset file size - resolution xy
	ScreenPosition sprite_center;
	std::pair<float, float> sprite_scale;

public:
	RenderableObject(); // vse podaj? setterji bolje, da lahko sistemi lepo nastavijo vse?
	~RenderableObject();

	virtual void render(Camera* camP);

};

