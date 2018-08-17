#pragma once

#include <iostream>
#include <fstream>

#include <array>
#include <vector>
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "RenderableObject.h"
#include "Util.h"
#include "Actor.h"
#include "game_object/Trap.h"
#include "game_object/Exit.h"

// WorldTile

enum WORLD_TILE_TYPE {
	TILE_TYPE_WALL = 0,
	TILE_TYPE_AIR,
	TILE_TYPE_FLOOR,
	TILE_TYPE_PLAYER_SPAWN_FAT,
	TILE_TYPE_PLAYER_SPAWN_SLIM,

	TILE_TYPE_TRAP,
	TILE_TYPE_EXIT
};

class WorldTile
{
private:

public:
	WORLD_TILE_TYPE type;

};


// WorldMap

class WorldMap : public RenderableObject
{
private:

	int size_x;
	int size_y;

	std::string path_to_map;
	std::vector<ALLEGRO_BITMAP*> assets;
	
	std::vector<WorldTile*> world_map; 
	std::vector<Object*> objects;

	void loadMap();

public:
	WorldMap();
	WorldMap(std::string pathToMap);
	~WorldMap();

	WorldTile& getTile(int x, int y);
	std::pair
		<
		std::vector<WorldTile*>::iterator,
		std::vector<WorldTile*>::iterator
		> 
		getMapIterators();

	std::vector<ALLEGRO_BITMAP*>& getAssets();

	// inherited from RenderableObject
	virtual void render(Camera* camP) override;

};


// World

class Environment
{
public:
	WorldMap worldMap;
	Actor fat;
	ALLEGRO_BITMAP* player_asset;
	ALLEGRO_BITMAP* trap_asset;
	ALLEGRO_BITMAP* exit_asset;

	Environment();
	~Environment();

	WorldMap& getMap();
	Camera* getCamera();

};


// for SYSTEMS
class WORLD_ACCESS {
protected:
	Environment* world;  // !todo: replace pointer with something a bit smarter
public:
	void assignWorld(Environment* w);
};