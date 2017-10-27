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

class WorldMap : public RenderableObject
{
private:
	int size_x;
	int size_y;
	std::string path_to_map;
	std::vector<WorldTile> world_map; 
	std::vector<ALLEGRO_BITMAP*> assets; // !slow? want contigous memory
	void loadMap();
public:
	WorldMap();
	WorldMap(std::string pathToMap);
	~WorldMap();

	WorldTile& getTile(int x, int y);
	std::pair<std::vector<WorldTile>::iterator,
		std::vector<WorldTile>::iterator> getMapIterators();

	std::vector<ALLEGRO_BITMAP*>& getAssets();

	// inherited from RenderableObject
	virtual void render(Camera* camP);

};


// World

class Environment
{
private:
	WorldMap worldMap;
	Camera camera;
public:
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