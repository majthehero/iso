#pragma once

#include<map>

#include "World.h"

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

	std::pair<int, int> getMemCoords() {
		// !todo: IMPORTANT document how it works!
		// !todo: FIGOURE OUT how it works!
	}

	

};

