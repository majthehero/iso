#pragma once

#include<map>

#include "Util.h"

class Camera
{
private:
	/* manually init position */
	WorldPosition world_position; 
	float scale;
public:
	Camera();
	~Camera();
	
	void move(WorldPosition deltaPos) {
		world_position.add(deltaPos);
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
	WorldPosition getWorldPosition() {
		return world_position;
	}

};

