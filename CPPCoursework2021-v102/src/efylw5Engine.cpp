#include "efylw5Engine.h"


void efylw5Engine::virtSetupBackgroundBuffer()
{
	
	SimpleImage image = ImageManager::loadImage(getCurrentState()->getImageURL(), true);
	image.renderImage(BaseEngine::getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
	//std::cout << getCurrentState()->getImageURL();
	if (!getCurrentState()->getChangeImage())
	{
		getCurrentState()->setChangeImage(true);
		ImageManager::destroyImageManager();
	}

}


void efylw5Engine::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) {
		case SDLK_RETURN:
			lockAndSetupBackground();
			efylw5Engine::setCurrentState(new tutorialState());
			setState(3);
			redrawDisplay();
			break;
		case SDLK_ESCAPE:
			destroyOldObjects(true);
			setExitWithCode(1);
		
	}
	
}

void efylw5Engine::virtDrawStringsUnderneath()
{
	char str[128];
	for (int i = 0; i < getCurrentState()->getStr().size(); ++i) {
		sprintf(str, getCurrentState()->getStr()[i], rand());
		drawForegroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, NULL);
	}

}

void efylw5Engine::virtDrawStringsOnTop()
{

}

int efylw5Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();

	destroyOldObjects(true);

	createObjectArray(4);

	storeObjectInArray(0, new SnakeObject(this,10,10));

	setAllObjectsVisible(true);

	return 0;
}
