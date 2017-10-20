#pragma once

#include "Camera.h"

class Renderable
{
public:
	Renderable();
	~Renderable();

	virtual void render(Camera* camP) = 0;

};

