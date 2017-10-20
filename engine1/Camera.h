#pragma once

#include<map>

#include "Util.h"

class Camera
{
public:
	Position position; // !todo: hide a copy to encapsulate and protect data :P
	float scale;

	Camera();
	~Camera();

	void move(Position deltaPos) {
		position.add(deltaPos);
	}

	std::pair<std::pair<int, int>, std::pair<int, int>> getMemCoords();

	float getScale();
	Position getScreenCoords(Position* itemPos);

	void setPosition(float x, float y);
	

};

