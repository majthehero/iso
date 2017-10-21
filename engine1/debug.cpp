#include "debug.h"

Debug::Debug()
{
	file_name = "log.txt";
	file.open(file_name,	std::fstream::app);
	file << "--- NEW LOG ---" << std::endl;
}

Debug::~Debug()
{
	file.close();
}

void Debug::logCameraTransformation(
	float x1, float y1,
	float x2, float y2 )
{
	std::cerr << "Debug::logCameraTransformation> ";
	std::cerr << "itemPos.x: " << x1 << "itemPos.y: " << y1 << std::endl;
	std::cerr << "sX:        " << x2 << "sY:        " << y2 << std::endl;
	std::cerr << std::endl;
}
