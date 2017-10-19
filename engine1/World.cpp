#include "World.h"



World::World()
{
}


World::~World()
{
}

const WorldMap& World::getMap()
{
	return worldMap;
}

WorldMap::WorldMap()
{
	// load assets
	// !hardcode: load assets from file
	ALLEGRO_BITMAP *bitmapP = al_load_bitmap("assets/grass.png");
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/dirt.png");
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/water.png");
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/wall.png");
	assets.push_back(bitmapP);

	// !placeholder: load map from file
	int tilecount = 0;
	for (WorldTile wt : world_map) {
		wt.type = static_cast<WORLD_TILE_TYPE>((tilecount++ / 3) % 4);
	}
}

WorldMap::~WorldMap()
{
	for (auto wt : world_map) {
		al_destroy_bitmap(assets.at(wt.type));
	}
}

WorldTile & WorldMap::getTile(int x, int y)
{
	return world_map.at(x + MAP_ROW * y);
}

std::array<WorldTile, MAP_SIZE>::iterator WorldMap::getMapBegin()
{
	return world_map.begin();
}

std::array<WorldTile, MAP_SIZE>::iterator WorldMap::getMapEnd()
{
	return world_map.end();
}

void WorldMap::render()
{
	Position tilePos = { 0, 0 };
	for (auto wt : world_map) {
		if (tilePos.x + 64 > 960) continue;
		if (tilePos.y + 64 > 540) continue;

		al_draw_bitmap(
			assets.at(wt.type),
			tilePos.x,
			tilePos.y,
			NULL);
		tilePos.x++;
		if (tilePos.x == MAP_ROW - 1) {
			tilePos.x = 0;
			tilePos.y++;
		}
	}
}
