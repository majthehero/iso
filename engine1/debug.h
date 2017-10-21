#pragma once

#include <iostream>
#include <fstream>
#include <string>

#define DEBUG

class Debug {
private:
	std::string file_name;
	std::ofstream file;

public:
	Debug();
	~Debug();

	static void logCameraTransformation(
		float x1, float y1,
		float x2, float y2);


};