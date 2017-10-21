#pragma once

#include<map>

#include "Util.h"

#include "debug.h"

class Camera
{
private:
	/* manually init position */
	// !todo: hide a copy to encapsulate and protect data
	// !todo: correct constructors to auto init position to 0,0
	WorldPosition position; 
	float scale;
public:
	Camera();
	~Camera();

	Debug __dbg;

	void move(WorldPosition deltaPos) {
		position.add(deltaPos);
	}

	/* returns map bounds that camera can see */
	std::pair<std::pair<int, int>, std::pair<int, int>> getMemCoords();
	
	/* returns current scale modifier */
	float getScale();

	/* sets scale mod */
	void setScale(float sc);

	/* returns item position cenverted from worldspace to screenspace */
	ScreenPosition camera2dTransform(WorldPosition* itemPos);

	/* sets camera's position to x, y */
	void setPosition(float x, float y);
	

};

