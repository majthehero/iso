#pragma once

#include "System.h"

// UI SUBSYSTEM

extern int frames_per_second;

// ui element
#define UI_EL_SIZE 48
class DrawableItem {

	typedef struct {
		bool render;
		bool devel;
		bool text;
		bool error;
	} Flags;

private:
	Flags flags;
public:
	ALLEGRO_BITMAP* icon;
	std::string text;

	DrawableItem();
	~DrawableItem();

	virtual void draw(float x, float y);
};

// ui container element
class DrawableContainer {
public:
	ALLEGRO_COLOR backC;
	std::string text;
	std::vector<DrawableItem*> elements;
	ScreenPosition position = { 0,0 };
	float size_x;
	float size_y;

	DrawableContainer();
	~DrawableContainer();

	virtual void draw();
};


class UISubSystem :
	public System
{
public:
	// members
	ALLEGRO_BITMAP* ui_overlay;
	std::vector<DrawableContainer> containers;

	// constructors
	UISubSystem();
	~UISubSystem();

	// Inherited via System
	virtual void update(float deltaT = 0.0f) override;

	// return results
	ALLEGRO_BITMAP* getOverlay();

};


/* RENDER SYSTEM */
// WORLD_ACCESS should be used read only until write access is locked
class RenderSystem : public System, public WORLD_ACCESS
{
private:
	int width, height;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* base_font;
	UISubSystem ui_system;
public:
	RenderSystem(MessageBus* msgBus);
	~RenderSystem();

	void render();

	// Inherited via System
	virtual void update(float deltaT) override;
};