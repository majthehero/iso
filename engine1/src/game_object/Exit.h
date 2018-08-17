

class Exit :
	public Object,
	public RenderableObject,
	public Collider,
	public GameObject
{

	Exit();

	// object
	void update(float deltaT) override;

	// renderable
	void render(Camera* camP) override;

	// collider
	void collide(Collider col) override;

	// effector
	void effect(GameObject* obj) override;


};