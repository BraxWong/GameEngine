#include "efylw5Engine.h"


void efylw5Engine::virtSetupBackgroundBuffer()
{
	char str[128];
	for (int i = 0; i < getCurrentState()->getStr().size(); ++i) {
		sprintf(str, getCurrentState()->getStr()[i]);
		drawBackgroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, NULL);
	}

}
