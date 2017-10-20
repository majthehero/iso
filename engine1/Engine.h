#pragma once

#include <array>
#include <vector>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "System.h"
#include "World.h"
#include "Messaging.h"

class Engine
{
public:
	Engine();
	~Engine();
};


int main();