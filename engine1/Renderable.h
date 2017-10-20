#pragma once

#define DEBUG_WIDTH 960
#define DEBUG_HEIGHT 540

#define TILE_SIZE 64

class Renderable
{
public:
	Renderable();
	~Renderable();

	virtual void render() = 0;
};

