#include "Input.h"



Input::Input()
{
	// setup
	al_install_keyboard();
	al_install_mouse();

}


Input::~Input()
{
}

int Input::update()
{
	// generate commands
	switch (al_get_key)

	return 0;
}

int Input::post()
{
	return 0;
}

int Input::read()
{
	return 0;
}
