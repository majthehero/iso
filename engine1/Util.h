#pragma once

#define DEBUG_WIDTH 960
#define DEBUG_HEIGHT 540

#define TILE_SIZE 64

class Position {
public:
	float x;
	float y;
	Position();
	Position(float x, float y);
	void add(Position p);
};