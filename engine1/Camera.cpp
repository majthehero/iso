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
// !slow: loops should be replaced with some real interator magic
*/
std::pair<std::pair<int, int>, std::pair<int, int>> Camera::getMemCoords()
{
	// worldspace frustum size from scale
	float frustum_x_size = DEBUG_WIDTH / (TILE_SIZE * scale);
	float frustum_y_size = DEBUG_HEIGHT / (TILE_SIZE * scale);
	
	float frustumLeftEdge = position.x - frustum_x_size / 2;
	float frustumRightEdge = position.x + frustum_x_size / 2;

	float frustumUpperEdge = position.y - frustum_y_size / 2;
	float frustumBottomEdge = position.y + frustum_y_size / 2;
	
	// round to larger area
	int x1 = floor(frustumLeftEdge);
	int x2 = ceil(frustumRightEdge);
	int y1 = floor(frustumUpperEdge);
	int y2 = ceil(frustumBottomEdge);
		
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
	// both camera and item are in worldspace
	float sX = itemPosWSpace->x - position.x;
	float sY = itemPosWSpace->y - position.y;
	// convert to screenspace - now sX is screen space modifier 
	sX *= TILE_SIZE;
	sY *= TILE_SIZE;
	// center around 0,0 for scale
	sX -= DEBUG_WIDTH / 2;
	sY -= DEBUG_HEIGHT / 2;
	// scale
	sX *= scale;
	sY *= scale;
	// recenter to middle of screen
	sX += DEBUG_WIDTH;
	sY += DEBUG_HEIGHT;

	// return pair pair
	ScreenPosition itemPosSSpace;
	itemPosSSpace.x = sX;
	itemPosSSpace.y = sY;

	__dbg.logCameraTransformation(
		itemPosWSpace->x, itemPosWSpace->y,
		itemPosSSpace.x, itemPosSSpace.y);

	return itemPosSSpace;
}

void Camera::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
