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

void WorldMap::loadMap()
{
	// open file
	std::ifstream file;
	file.open(path_to_map);
	std::cerr << path_to_map << std::endl;
	if (!file) {
		std::cerr << "fuck\n";
		return;
	}
	// read metadata
	std::string line;
	std::getline(file, line);
	std::cerr << line << std::endl;
	size_x = std::stoi(line);
	std::getline(file, line);
	std::cerr << line << std::endl;
	size_y = std::stoi(line);
	
	// prepare tile
	WorldTile wt;

	// read map by char
	for (int i = 0; i < size_y; i++) {
		std::getline(file, line);
		for (char c : line) {
			switch (c) {
			case 'w':
				wt.type = TILE_TYPE_WALL;
				break;
			case 'd':
				wt.type = TILE_TYPE_DIRT;
				break;
			case 'g':
				wt.type = TILE_TYPE_GRASS;
				break;
			case '-':
				wt.type = TILE_TYPE_WATER;
				break;
			}
			world_map.push_back(wt);
		}
	}
	
	file.close();
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
	//int tilecount = 0;
	//for (WorldTile wt : world_map) {
	//	wt.type = static_cast<WORLD_TILE_TYPE>((tilecount++ / 3) % 4);
	//	//std::cerr << "Generated tile." << wt.type << "\n";
	//}
	//std::cerr << "Generated map.\n";
	
	// !placeholder: path to map
	path_to_map = "map_demo.txt";
	//clear map and load from file
	world_map.clear();
	loadMap();
	std::cerr << "Loaded map.\n";
	
}

WorldMap::WorldMap(std::string pathToMap)
{
	path_to_map = pathToMap;
	WorldMap();
}

WorldMap::~WorldMap()
{
	for (auto wt : world_map) {
		al_destroy_bitmap(assets.at(wt.type));
	}
}

WorldTile & WorldMap::getTile(int x, int y)
{
	return world_map.at(x + size_x * y);
}

std::pair<std::vector<WorldTile>::iterator, std::vector<WorldTile>::iterator> WorldMap::getMapIterators()
{
	std::pair<std::vector<WorldTile>::iterator,
		std::vector<WorldTile>::iterator> p;
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
	std::cerr << "worldmap::render::camP->pos: " << camP->position.x << " , " << camP->position.y << std::endl;

	WorldPosition itemPosSSpace{ 0,0 };
	// !slow: loops should be replaced with some real interator magic
	auto p = camP->getMemCoords(); // <<xBeg, xEnd>, <yBeg, yEnd>>
	int iBegin = p.first.first; 
	int iEnd = p.first.second;
	int jBegin = p.second.first;
	int jEnd = p.second.second;
	
	WorldPosition itemPos(0.0f, 0.0f);

	for ( ; jBegin < jEnd; jBegin++ )
	{
		for ( iBegin = p.second.first; iBegin < iEnd; iBegin++ ) // reset on new row
		{
		
			if (jBegin < 0 || jBegin >= size_y) continue; // out of mem, don't draw
			if (iBegin < 0 || iBegin >= size_x) continue; // out of mem, don't draw
		
			WorldTile wt = getTile(iBegin, jBegin);
			float srcScale = TILE_SIZE;
			float destScale = TILE_SIZE * camP->getScale();
		
			itemPos.x = iBegin;
			itemPos.y = jBegin;
			itemPosSSpace = camP->camera2dTransform(&itemPos);
			
			al_draw_scaled_bitmap(
				assets.at(wt.type),		// bitmap
				0, 0,					// src xy
				srcScale, srcScale,		// src scale
				itemPosSSpace.x,		// dest x
				itemPosSSpace.y,			//  y
				destScale, destScale,	// dest scale
				NULL);
			//al_draw_text(base_font, )
		}
	}
}

void WORLD_ACCESS::assignWorld(World* w)
{
	world = w;
}

