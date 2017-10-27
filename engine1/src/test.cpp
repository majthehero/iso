#include <iostream>
#include <allegro5/allegro.h>

int main () {
	
	bool allegro_installed = al_init();
	if (allegro_installed) {
		std::cout << "Succesfull initialization!" << std::endl;
		uint32_t version = al_get_allegro_version();
		int major = version >> 24;
		int minor = (version >> 16) & 255;
		int revision = (version >> 8) & 255;
		int release = version & 255;
		std::cout << "Version " << major << "." << minor << "." << revision << "." << "release" << std::endl;
	}
	
	return 0;

}
