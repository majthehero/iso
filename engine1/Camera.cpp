#include "Camera.h"



Camera::Camera()
{
	scale = 1.0;
	setPosition(0.0f, 0.0f);
}


Camera::~Camera()
{
}

/*
returns: pair<pair<int, int>pair<int, int>>: xMin, xMax, yMin, yMax
*/
std::pair<std::pair<int, int>, std::pair<int, int>> Camera::getMemCoords()
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int xNum = 0;
	int yNum = 0;
	
	// scale
	float relTileSize = (TILE_SIZE * scale);
	xNum = ceil(DEBUG_WIDTH / relTileSize);
	yNum = ceil(DEBUG_HEIGHT / relTileSize);
	
	// center on position
	x1 = position.x / relTileSize - xNum / 2;
	y1 = position.y / relTileSize - yNum / 2;
	x2 = x1 + xNum;
	y2 = y1 + xNum;

	std::pair<std::pair<int, int>, std::pair<int, int>> p;
	std::pair<int, int> xBound(x1, x2);
	std::pair<int, int> yBound(y1, y2);

	p.first = xBound;
	p.second = yBound;
		
	return p;
}

float Camera::getScale()
{
	return scale;
}

/*
itemPos: position of item in world space - unit is tile
returns: position of item in screen space - unit is pixel
*/
Position Camera::getScreenCoords(Position* itemPosWSpace)
{
	float sX = itemPosWSpace->x * TILE_SIZE - position.x;
	float sY = itemPosWSpace->y * TILE_SIZE - position.y;
	// recenter before scale
	sX -= DEBUG_WIDTH / 2;
	sY -= DEBUG_HEIGHT / 2;
	// scale
	sX *= scale;
	sY *= scale;
	// recenter after scale
	sX += DEBUG_WIDTH / 2;
	sY += DEBUG_HEIGHT / 2;

	Position itemPosSSpace;
	itemPosSSpace.x = sX;
	itemPosSSpace.y = sY;


	return itemPosSSpace;
}

void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
