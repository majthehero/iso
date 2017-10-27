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
