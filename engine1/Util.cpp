#include "Util.h"

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(float x, float y)
{
	x = x;
	y = y;
}

void Position::add(Position p)
{
	x += p.x;
	y += p.y;
}
