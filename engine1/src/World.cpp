#include "World.h"

Environment::Environment()
{
	// init camera
	camera.setPosition(0.0f, 0.0f);
}


Environment::~Environment()
{
}

WorldMap& Environment::getMap()
{
	return worldMap;
}

Camera * Environment::getCamera()
{
	return &camera;
}

void WorldMap::loadMap()
{
	// open file
	std::ifstream file;
	file.open(path_to_map);
	if (!file) {
		std::cerr << "ERROR: failed to load map: " << path_to_map << std::endl;
		return;
	}

	// read metadata
	std::string line;
	std::getline(file, line);
	size_x = std::stoi(line);
	std::getline(file, line);
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
	// !hardcode: load assets from file - why tho, it's kinda the same
	ALLEGRO_BITMAP *bitmapP = al_load_bitmap("assets/grass.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/grass.png" << std::endl;
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/dirt.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/dirt.png" << std::endl;
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/water.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/water.png" << std::endl;
	assets.push_back(bitmapP);
	bitmapP = al_load_bitmap("assets/wall.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/wall.png" << std::endl;
	assets.push_back(bitmapP);
		
	// !placeholder: path to map - probably multiple maps, hot load
	path_to_map = "map_demo.txt";
	
	//clear map and load from file
	world_map.clear();
	loadMap();
		
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
	ScreenPosition itemPosSP{ 0,0 };
	// !slow: loops should be replaced with some real interator magic
	auto p = camP->getMemCoords(); // <<xBeg, xEnd>, <yBeg, yEnd>>
	int iBegin = p.first.first; 
	int iEnd = p.first.second;
	int jBegin = p.second.first;
	int jEnd = p.second.second;
	std::cerr << "INFO: render got mem coords: x " << iBegin << " - " << iEnd
		<< " y " << jBegin << " - " << jEnd << std::endl;

	WorldPosition itemPos(0.0f, 0.0f);
	
	for ( jBegin = p.second.first; jBegin < jEnd; jBegin++ )
	{
		std::cerr << "INFO: jBegin value: " << jBegin << std::endl;
		for ( iBegin = p.first.first; iBegin < iEnd; iBegin++ ) // reset on new row
		{
			std::cerr << "INFO: iBegin value: " << iBegin << std::endl;

			//std::cerr << "\nINFO: render tile " << jBegin << " " << iBegin;
			if (jBegin < 0 || jBegin >= size_y) continue; // out of mem, don't draw
			if (iBegin < 0 || iBegin >= size_x) continue; // out of mem, don't draw

			WorldTile wt = getTile(iBegin, jBegin);
			
			float srcScale = TILE_SIZE;
			float destScale = TILE_SIZE * camP->getScale();
		
			itemPos.x = iBegin;
			itemPos.y = jBegin;
			itemPosSP = camP->camera2dTransform(&itemPos);
			
			if (flags.render)
				al_draw_scaled_bitmap(
					assets.at(wt.type),		// bitmap
					0, 0,					// src xy
					srcScale, srcScale,		// src scale
					itemPosSP.x,		// dest x
					itemPosSP.y,			//  y
					destScale, destScale,	// dest scale
					NULL);
			if (flags.devel)
				al_draw_text(base_font, fontC,
					itemPosSP.x,		// dest x
					itemPosSP.y,			//  y
					NULL,				// flags
					text.c_str());		// text c string
		}
	}
	// close those INFO lines
	std::cerr << std::endl;
}

void WORLD_ACCESS::assignWorld(Environment* w)
{
	world = w;
}

