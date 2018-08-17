#include "World.h"

#include <iostream>
#include "game_object/Trap.h"
#include "game_object/Exit.h"

// environment

Environment::Environment()
{
	printf("Environment constructor. Loading assets.");
	
	player_asset = al_load_bitmap("assets/Others/AgentPlume1.png");
	if (!player_asset) std::cerr << "ERROR: asset load failed: assets/others/AgentPlume1.png" << std::endl;

	trap_asset = al_load_bitmap("assets/Animated/trap_animateds.png");

	fat.setSprite(player_asset);
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
	return & this->fat.camera;
}


// world map

void WorldMap::loadMap()
{
	printf("	Loading map.");

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
	Object obj;
	// read map by char
	for (int i = 0; i < size_y; i++) {
		std::getline(file, line);
		for (char c : line) {
			switch (c) {
			case 'W':
				wt.type = TILE_TYPE_WALL;
				//std::cout << "wall" << std::endl;
				world_map.push_back(wt);
				break;

			case '.':
				wt.type = TILE_TYPE_AIR;
				world_map.push_back(wt);
				break;

			case '_':
				wt.type = TILE_TYPE_FLOOR;
				world_map.push_back(wt);
				break;
			
			case 'P':
				wt.type = TILE_TYPE_PLAYER_SPAWN_FAT;
				world_map.push_back(wt);
				break;

			case 'p':
				wt.type = TILE_TYPE_PLAYER_SPAWN_SLIM;
				world_map.push_back(wt);
				break;

			case 'T':
				obj = Trap(); // TODO put it in place
				
				this->objects.push_back(obj);
				break;

			case 'X':
				obj = Exit(); // TODO put it in place 
			}
			
		}
	}
	
	for (WorldTile wt : world_map) {
		printf("%d\n", (int)wt.type);
	}

	file.close();
}

WorldMap::WorldMap()
{
	printf("WorldMap constructor.");

	// load assets
	// !hardcode: load assets from file - why tho, it's kinda the same
	
	ALLEGRO_BITMAP *bitmapP = al_load_bitmap("assets/wall.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/wall.png" << std::endl;
	assets.push_back(bitmapP);
	
	bitmapP = al_load_bitmap("assets/Others/Air.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/others/Air.png" << std::endl;
	assets.push_back(bitmapP);

	bitmapP = al_load_bitmap("assets/grass.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/grass.png" << std::endl;
	assets.push_back(bitmapP);

	bitmapP = al_load_bitmap("assets/Others/AgentPlume0.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/others/AgentPlume0.png" << std::endl;
	assets.push_back(bitmapP);

	bitmapP = al_load_bitmap("assets/Others/AgentPlume1.png");
	if (!bitmapP) std::cerr << "ERROR: asset load failed: assets/others/AgentPlume1.png" << std::endl;
	assets.push_back(bitmapP);


	// !placeholder: path to map - probably multiple maps, hot load
	path_to_map = "assets/others/level0.map";
	
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

	auto p = camP->getMemCoords(); // <<xBeg, xEnd>, <yBeg, yEnd>>
	int iBegin = p.first.first; 
	int iEnd = p.first.second;
	int jBegin = p.second.first;
	int jEnd = p.second.second;
	
	WorldPosition itemPos(0.0f, 0.0f);
	
	for ( jBegin = p.second.first; jBegin < jEnd; jBegin++ )
	{
		for ( iBegin = p.first.first; iBegin < iEnd; iBegin++ ) // reset on new row
		{
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

			if (flags.devel) {
				char coords_str[20];
				sprintf_s(coords_str, 20,  "%d: %d,%d ", (int)wt.type, (int)itemPos.x, (int)itemPos.y);
				if (!coords_str) sprintf_s(coords_str, 20, "err");
				al_draw_text(base_font, fontC,
					itemPosSP.x,		// dest x
					itemPosSP.y,			//  y
					NULL,				// flags
					coords_str);		// text c string
			}
			
		}
	}
}

void WORLD_ACCESS::assignWorld(Environment* w)
{
	world = w;
}

