#include "World.h"



World::World()
{
}


World::~World()
{
}

WorldMap& World::getMap()
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
		//std::cerr << "Generated tile." << wt.type << "\n";
	}
	std::cerr << "Generated map.\n";
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

std::pair<std::array<WorldTile, MAP_SIZE>::iterator, std::array<WorldTile, MAP_SIZE>::iterator> WorldMap::getMapIterators()
{
	std::pair<std::array<WorldTile, MAP_SIZE>::iterator,
		std::array<WorldTile, MAP_SIZE>::iterator> p;
	p.first = world_map.begin();
	p.second = world_map.end();
	return p;
}


std::vector<ALLEGRO_BITMAP*>& WorldMap::getAssets()
{
	return assets;
}

void WorldMap::render() // !todo: replace with code from RenderSystem::render()
{
	Position tilePos = { 0, 0 };
	for (auto wt : world_map) {
		if (tilePos.x + TILE_SIZE > DEBUG_WIDTH) continue; // !hardcoded: blargh
		if (tilePos.y + TILE_SIZE > DEBUG_WIDTH) continue;

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

void WORLD_ACCESS::assignWorld(World* w)
{
	world = w;
}

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(float x, float y)
{
	x = x;
	y = y;
}

void Position::add(Position p)
{
	x += p.x;
	y += p.y;
}
