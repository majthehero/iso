#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#include "System.h"
#include "World.h"
#include "Messaging.h"

// timing
float deltaT;
float previous_time;
int frames_per_second;

double getDeltaTime();

// ui

// draw fps count
ALLEGRO_FONT* base_font;




// main
int main();