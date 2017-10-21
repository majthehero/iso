#include "Util.h"

WorldPosition::WorldPosition()
{
	x = 0;
	y = 0;
}

WorldPosition::WorldPosition(float x, float y)
{
	x = x;
	y = y;
}

void WorldPosition::add(WorldPosition p)
{
	x += p.x;
	y += p.y;
}
