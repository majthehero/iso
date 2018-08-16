#pragma once

#include "Util.h"
#include "RenderableObject.h"

class Actor : public RenderableObject
{
public:
	Actor();
	~Actor();

	float momentum_x;
	float momentum_y;

	

	enum PlayerType {
		FAT,
		SLIM
	};

	enum PlayerType playerType;

	// execute game space commands
	
	void moveLeft() 
	{
		this->momentum_x -= 1.0;
	}

	void moveRight()
	{
		this->momentum_x =+ 1.0;
	}

	void jump()
	{
		this->momentum_y += 1.0;
	}

	void roll()
	{
		;;
	}

	void render(Camera* camP)
	{
		ScreenPosition itemPosSP{ 0,0 };

		auto p = camP->getMemCoords(); // <<xBeg, xEnd>, <yBeg, yEnd>>
		int iBegin = p.first.first;
		int iEnd = p.first.second;
		int jBegin = p.second.first;
		int jEnd = p.second.second;
	}
};

