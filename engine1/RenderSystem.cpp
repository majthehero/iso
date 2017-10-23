#include "RenderSystem.h"

#include "debug.h"



RenderSystem::RenderSystem(MessageBus* msgBusP)
{
	messages = msgBusP;
	width = 960;
	height = 540;
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
	world->getMap().render(world->getCamera());

	// update ui 
	ui_system.update();
	// blend ui overlay on top of render
	al_draw_bitmap(ui_system.getOverlay(), 0.0f, 0.0f, NULL);

	// show render
	al_flip_display(); // must be called at the end of render step
}

void RenderSystem::update()
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
			else 
			{
				std::cerr << "lol wut" << std::endl;
			}
		}
	}
};



// UI SUBSYSTEM

// DRAWABLE ITEM

DrawableItem::DrawableItem()
{
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
	std::cerr << "item being drawn";
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
	std::cerr << position.x << " " << position.y << std::endl;
	std::cerr << position.x + size_x << " " << position.y + size_y << std::endl;
	std::cerr << backC.r << " " << backC.g << " " << backC.b << " " << backC.a << std::endl;

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
		std::cerr << "drawing element " << column << " " << row << std::endl;
		item_x += padding;
		element->draw(item_x, item_y);
		column++;
		item_x += UI_EL_SIZE;
		std::cerr << "x, y " << item_x << " " << item_y << std::endl;
		std::cerr << "col, row " << column << " " << row << std::endl;

		if ((row)* UI_EL_SIZE > size_x) {
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
	std::cout << "UIsystem init\n";
	// test
	DrawableContainer c1;
	c1.position = ScreenPosition(20.0f, 20.0f);
	c1.size_x = 180;
	c1.size_y = 120;
	c1.elements.push_back(new DrawableItem());
	c1.elements.push_back(new DrawableItem());
	c1.elements.push_back(new DrawableItem());
	c1.elements.push_back(new DrawableItem());
	c1.elements.push_back(new DrawableItem());
	containers.push_back(c1);
	//
	ui_overlay = al_create_bitmap(DEBUG_WIDTH, DEBUG_HEIGHT);
}


UISubSystem::~UISubSystem() {
	al_shutdown_primitives_addon();
}

void UISubSystem::update() // currently works as render for testing purposes
{
	// draw on a sepparate layer
	ALLEGRO_DISPLAY* displ = al_get_current_display();
	al_set_target_bitmap(ui_overlay);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0)); // set overlay buffer to empty
	// read messages
	std::pair < std::vector<Message>::iterator,
		std::vector<Message>::iterator> p = messages->getIterators();
	for (; p.first != p.second; p.first++) {
		if (p.first->shouldRemove()) continue;
		if (p.first->getDest() == SYS_UI) {
			if (p.first->shouldRemove()) continue;
			
			switch (p.first->getCommand()) {
			case CMD_UI:
				std::cout << "ui update\n";
				for (auto c : containers) {
					c.draw();
				}
				p.first->shouldRemove();
			}

		}
	}
	//al_set_target_bitmap(al_get_backbuffer(displ));
	al_set_target_backbuffer(displ);

}

ALLEGRO_BITMAP * UISubSystem::getOverlay()
{
	return ui_overlay;
}
