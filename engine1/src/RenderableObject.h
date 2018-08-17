#pragma once

#include <iostream>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\color.h>

#include "Util.h"
#include "Camera.h"

extern ALLEGRO_FONT* base_font;


class Object
{
public:
	virtual void update(float deltaT) {};
};

class RenderableObject
{
protected:
	ALLEGRO_BITMAP* empty_sprite;
	ALLEGRO_COLOR backC;
	ALLEGRO_COLOR fontC;

	typedef struct {
		bool render;
		bool devel; // will render id on object
		bool error;
		bool err_sprite;
	} Flags;

	Flags flags;

public:
	WorldPosition world_position;
	ALLEGRO_BITMAP* spriteP;
	std::pair<int, int> sprite_size; // asset file size - resolution xy
	ScreenPosition sprite_center;
	std::pair<float, float> sprite_scale;

	std::string text;
	int object_id;

public:
	RenderableObject(); // vse podaj? setterji bolje, da lahko sistemi lepo nastavijo vse?
	~RenderableObject();

	virtual void render(Camera* camP) = 0;
	virtual void setSprite(ALLEGRO_BITMAP* spriteP) 
	{ 
		this->spriteP = spriteP;
	};

};

class Collider
{
public:

	typedef struct {
		float min_x;
		float max_x;
		float min_y;
		float max_y;
	} BoundingBox;

	BoundingBox boundingBox;

public:

	Collider() {};
	~Collider() {};

	virtual bool collide(Collider* col) = 0;

};

class GameObject
{
public:

	enum ObjectType { // keep bit-objand-able
		deal_damage			= 0b0001,
		receive_damage		= 0b0010,
	};

	ObjectType objectType;

public:

	GameObject() {};
	~GameObject() {};

	virtual void effect(GameObject* obj) = 0; 
};