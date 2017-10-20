#pragma once

#include <iostream>

#include <array>
#include <vector>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "Renderable.h"

// Position !todo move to a different file
class Position {
public:
	float x;
	float y;	
	Position();
	Position(float x, float y);
	void add(Position p);
} ;

// WorldTile

enum WORLD_TILE_TYPE {
	TILE_TYPE_GRASS = 0,
	TILE_TYPE_DIRT,
	TILE_TYPE_WATER,
	TILE_TYPE_WALL
};

class WorldTile
{
private:

public:
	WORLD_TILE_TYPE type;

};


// WorldMap
#define MAP_ROW 128
#define MAP_SIZE (128*128)

class WorldMap : public Renderable
{
private:
	std::array<WorldTile, MAP_SIZE> world_map; // !hardcode: size def
	std::vector<ALLEGRO_BITMAP*> assets; // !slow? wanted contigous memory
	
public:
	WorldMap();
	~WorldMap();

	WorldTile& getTile(int x, int y);
	std::pair<std::array<WorldTile, MAP_SIZE>::iterator,
		std::array<WorldTile, MAP_SIZE>::iterator> getMapIterators();

	std::vector<ALLEGRO_BITMAP*>& getAssets();

	// Inherited via Renderable
	virtual void render() override;

};


// World

class World
{
private:
	WorldMap worldMap;

public:
	World();
	~World();

	WorldMap& getMap();
};


// for SYSTEMS
class WORLD_ACCESS {
protected:
	World* world;  // !todo: replace pointer with something a bit smarter
public:
	void assignWorld(World* w);

};