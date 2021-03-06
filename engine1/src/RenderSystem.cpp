#include "RenderSystem.h"

RenderSystem::RenderSystem(MessageBus* msgBusP)
{
	messages = msgBusP;
	width = DEBUG_WIDTH;
	height = DEBUG_HEIGHT;
	display = al_create_display(width, height);
	ui_system.setMessageBus(msgBusP);
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::render()
{
	// clear frame
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	// render game
	world->getMap().render(&world->fat.camera);
	world->fat.render(&world->fat.camera);

	// update ui 
	ui_system.update();
	// blend ui overlay on top of render
	al_draw_bitmap(ui_system.ui_overlay, 0.0f, 0.0f, NULL);

	// show render
	al_flip_display(); // must be called at the end of render step
}

void RenderSystem::update(float deltaT)
{
	auto iBegin = messages->getIterator();
	auto iEnd = messages->iteratorEnd();
	for ( ; iBegin != iEnd; iBegin++) 
	{
		if (iBegin->shouldRemove()) continue;
		if (iBegin->getDest() == SYS_RENDER) 
		{
			if (iBegin->getCommand() == CMD_RENDER) 
			{
				render();
				iBegin->mark_remove();
			}
		}
	}
};



// UI SUBSYSTEM

// DRAWABLE ITEM

DrawableItem::DrawableItem()
{
	flags = { true, true, true, false };

	ALLEGRO_DISPLAY* displ = al_get_current_display();
	icon = al_create_bitmap(UI_EL_SIZE, UI_EL_SIZE);
	al_set_target_bitmap(icon);
	al_clear_to_color(al_map_rgba_f(0.5f, 0.5f, 0.5f, 0.5f)); // grey
	al_set_target_bitmap(al_get_backbuffer(displ));
	text = "default";
}

DrawableItem::~DrawableItem()
{
	al_destroy_bitmap(icon);
}

void DrawableItem::draw(float x, float y)
{
	if (flags.render) 
		al_draw_bitmap(icon, x, y, NULL);
	
}



// DRAWABLE CONTAINER

DrawableContainer::DrawableContainer()
{
	backC = al_map_rgba_f(1.0, 0.4f, 1.0f, 0.3f);
	text = "default";
	position.x = 0.0f;
	position.y = 0.0f;
	size_x = 0.0f;
	size_y = 0.0f;
}

DrawableContainer::~DrawableContainer() { }

void DrawableContainer::draw()
{
	al_draw_filled_rounded_rectangle(position.x, position.y,
		position.x + size_x, position.y + size_y, 5.0f, 5.0f, backC);
	float item_x = position.x + 5.0f;
	float item_x_start = position.x + 5.0f;
	float item_y = position.x + 5.0f;
	float padding = 5.0f;
	int	item_no = 0;
	int column = 0;
	int row = 0;
	for (auto element : elements) {

		item_x += padding;
		element->draw(item_x, item_y);
		column++;
		item_x += UI_EL_SIZE;

		if ((column)* UI_EL_SIZE > size_x) {
			column = 0;
			item_x = item_x_start;
			item_y += padding + UI_EL_SIZE;
			row++;
			if ((item_y + padding + UI_EL_SIZE) > size_y) {
				break; // no more items fit in this container
					   // !todo: add support for scrolling
			}
		}
	}
}



// US SYSTEM

UISubSystem::UISubSystem()
{
	ui_overlay = al_create_bitmap(DEBUG_WIDTH, DEBUG_HEIGHT);
}


UISubSystem::~UISubSystem() {
	al_shutdown_primitives_addon();
}

void UISubSystem::update(float deltaT) // currently works as render for testing purposes
{
	// draw on a sepparate layer
	ALLEGRO_DISPLAY* displ = al_get_current_display();
	al_set_target_bitmap(ui_overlay);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0)); 
	
	// read messages
	std::pair < std::vector<Message>::iterator,
		std::vector<Message>::iterator> p = messages->getIterators();
	for (; p.first != p.second; p.first++) {
		if (p.first->shouldRemove()) continue;
		if (p.first->getDest() == SYS_UI) {
			if (p.first->shouldRemove()) continue;
			
			switch (p.first->getCommand()) {
			case CMD_UI:
				for (auto c : containers) {
					c.draw();
				}
				p.first->mark_remove();
			}

		}
	}

	// draw fps count on top of all else
	char fps_str[20];
	sprintf_s(fps_str, 20, "%d ", frames_per_second);
	al_draw_text(base_font, al_map_rgb_f(1, 1, 1), 5, 5, NULL, fps_str);

	// retuen allegro to normal state
	al_set_target_backbuffer(displ);
}

ALLEGRO_BITMAP * UISubSystem::getOverlay()
{
	return ui_overlay;
}
