#include "World.h"

#include "debug.h"

World::World()
{
	// init camera
	camera.setPosition(0.0f, 0.0f);
}


World::~World()
{
}

WorldMap& World::getMap()
{
	return worldMap;
}

Camera * World::getCamera()
{
	return &camera; // !todo: replace pointer
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

void WorldMap::render(Camera* camP) 
{
	Position pos{ 0,0 };
	// !slow: loops should be replaced with some real interator magic
	auto p = camP->getMemCoords(); // <<xBeg, xEnd>, <yBeg, yEnd>>
	int iBegin = p.first.first; 
	int iEnd = p.first.second;
	int jBegin = p.second.first;
	int jEnd = p.second.second;
	
	Position itemPos(0.0f, 0.0f);

	for ( ; jBegin < jEnd; jBegin++ )
	{
		for ( iBegin = p.second.first; iBegin < iEnd; iBegin++ ) // reset on new row
		{
		
			if (jBegin < 0 || jBegin > MAP_SIZE / MAP_ROW) continue; // out of mem, don't draw
			if (iBegin < 0 || iBegin > MAP_ROW) continue; // out of mem, don't draw
		
			WorldTile wt = getTile(iBegin, jBegin);
			float srcScale = TILE_SIZE;
			float destScale = TILE_SIZE * camP->getScale();
		
			itemPos.x = iBegin;
			itemPos.y = jBegin;

			pos = camP->getScreenCoords(&itemPos);
			
			std::cerr << "posx= " << pos.x << std::endl;
			std::cerr << "posy= " << pos.y << std::endl;

			al_draw_scaled_bitmap(
				assets.at(wt.type),		// bitmap
				0, 0,					// src xy
				srcScale, srcScale,		// src scale
				pos.x, pos.y,			// dest xy
				destScale, destScale,	// dest scale
				NULL);
		}
	}
}

void WORLD_ACCESS::assignWorld(World* w)
{
	world = w;
}

