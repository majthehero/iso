#include "Camera.h"

#include <iostream>

#include "Util.h"


Camera::Camera()
{
	scale = 1.0;
	setPosition(0.0f, 0.0f);
}


Camera::~Camera()
{
}

/* What needs loading - view culling
Tested, works.
returns: pair<pair<int, int>pair<int, int>>: xMin, xMax, yMin, yMax
// !slow: loops should be replaced with some real interator magic
*/
std::pair<std::pair<int, int>, std::pair<int, int>> Camera::getMemCoords()
{
	// everything is worldspace
	float cX = world_position.x;
	float cY = world_position.y;
	// how many tiles are on screen
	float tilesX = (float)DEBUG_WIDTH / (float)TILE_SIZE;
	float tilesY = (float)DEBUG_HEIGHT / (float)TILE_SIZE;
	// get world space visible bounds
	float x1 = cX - tilesX;
	float x2 = cX + tilesX;
	float y1 = cY - tilesY;
	float y2 = cY + tilesY;
	// round away from 0 to include partially visible tiles
	int xL = std::floor(x1);
	int xR = std::ceil(x2);
	int yU = std::floor(y1);
	int yD = std::ceil(y2);

	// return object pair<pair<>>
	std::pair<std::pair<int, int>, std::pair<int, int>> p;
	std::pair<int, int> xBound(xL, xR);
	std::pair<int, int> yBound(yU, yD);

	p.first = xBound;
	p.second = yBound;
		
	return p;
}

float Camera::getScale()
{
	return scale;
}

void Camera::setScale(float sc)
{
	scale = sc;
}

/*
itemPos: position of item in world space - unit is tile
returns: position of item in screen space - unit is pixel
*/
ScreenPosition Camera::camera2dTransform(WorldPosition* itemPosWSpace)
{
	// worldspace to screenspace conversion
	float iX = itemPosWSpace->x * TILE_SIZE * scale;
	float iY = itemPosWSpace->y * TILE_SIZE * scale;
	float cX = world_position.x * TILE_SIZE * scale;
	float cY = world_position.y * TILE_SIZE * scale;
	iX -= cX;
	iY -= cY;

	// return pair pair
	ScreenPosition itemPosSSpace;
	itemPosSSpace.x = iX;
	itemPosSSpace.y = iY;

	return itemPosSSpace;
}

void Camera::setPosition(float x, float y)
{
	world_position.x = x;
	world_position.y = y;
}


void Camera::update()
{

}