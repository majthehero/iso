#include "../RenderableObject.h"
#include "../World.h"

class Exit :
	public Object,
	public RenderableObject,
	public Collider,
	public GameObject,
	public WORLD_ACCESS
{
public:
	Exit();

	// object
	void update(float deltaT) override;

	// renderable
	void render(Camera* camP) override;

	// collider
	bool collide(Collider* col) override;

	// effector
	void effect(GameObject* obj) override;


};