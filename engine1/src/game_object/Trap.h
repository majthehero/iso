#include "../RenderableObject.h"

#include "World.h"
#include "../Util.h"

class Trap : 
	public Object,
	public RenderableObject,
	public Collider,
	public GameObject,
	public WORLD_ACCESS
{
private:
	float since_frame_one = 0;


public:
	Trap();
	Trap(float pos_x, float pos_y);

	// object

	void update(float deltaT);

	// renderable

	void render(Camera* camP) override;
	

	// effector

	void effect(GameObject* obj) override;

	// collider
	
	bool collide(Collider* col) override;
};