#pragma once

#include "Util.h"
#include "RenderableObject.h"
#include "Camera.h"


class Actor : 
	public RenderableObject,
	public GameObject,
	public Collider
{
public:
	Actor();
	~Actor();

	void setSprite(ALLEGRO_BITMAP* spriteP);

	float momentum_x = 0.0f;
	float momentum_y = 0.0f;

	Camera camera;

	enum PlayerType {
		FAT,
		SLIM
	};

	enum PlayerType playerType;

	enum PlayerState {
		IDLE,
		JUMPING,
		LEFT,
		RIGHT
	};
	PlayerState playerState = IDLE;

	// renderable object

	// game object

	// collider

	bool collide(Collider* col)
	{
		if (this->boundingBox.max_x > col->boundingBox.min_x &&
			this->boundingBox.min_x < col->boundingBox.max_x &&
			this->boundingBox.max_y > col->boundingBox.min_y &&
			this->boundingBox.min_y < col->boundingBox.min_y)
		{
			return true;
		}
	}

	// Actor methods

	void moveLeft()
	{
		if (playerState == IDLE) {
			this->momentum_x = -1.0;
			playerState = LEFT;
		}
		else if (playerState == JUMPING) {
			this->momentum_x = -0.5;
		}
		else if (playerState == RIGHT) {
			this->momentum_x = 0.0;
			this->playerState = IDLE;
		}
	}

	void moveRight()
	{
		if (playerState == IDLE) {
			this->momentum_x = 1.0;
			playerState = RIGHT;
		}
		else if (playerState == JUMPING) {
			this->momentum_x = 0.5;
		}
		else if (playerState == LEFT) {
			this->momentum_x = 0.0;
			this->playerState = IDLE;
		}
	}

	void jump()
	{
		if (playerState == IDLE) {
			this->momentum_x = 0.0;
			this->momentum_y = 1.0;
			this->playerState = JUMPING;
		}
		else if (playerState == RIGHT) {
			this->momentum_x = 1.0;
			this->momentum_y = 0.5;
			this->playerState = JUMPING;
		}
		else if (playerState == LEFT) {
			this->momentum_x = -1.0;
			this->momentum_y = 0.5;
			this->playerState = JUMPING;
		}
		else {
			;; // when jumping jump does nothing.
		}

	}

	void roll()
	{
		;;
	}

	void render(Camera* camP)
	{
		ScreenPosition position_screen;

		position_screen = camP->camera2dTransform(&this->world_position);

		al_draw_bitmap(spriteP, position_screen.x, position_screen.y, NULL);
	}

	void update(float deltaT);
};

