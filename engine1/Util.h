#pragma once

#define DEBUG_WIDTH 960
#define DEBUG_HEIGHT 540

#define TILE_SIZE 64

class WorldPosition {
public:
	float x;
	float y;
	WorldPosition();
	WorldPosition(float x, float y);
	void add(WorldPosition p);
};

class ScreenPosition {
public:
	float x;
	float y;
	ScreenPosition();
	ScreenPosition(float x, float y);
	void add(WorldPosition p);
};