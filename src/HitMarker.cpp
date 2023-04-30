#include "HitMarker.h"
#include "header.h"
#include "SnakeObject.h"
#include "BaseEngine.h"
#include "efylw5Engine.h"
#include "UtilCollisionDetection.h"

HitMarker::HitMarker(efylw5Engine* ptrEngine, int x, int y)
	:DisplayableObject(ptrEngine),
	ptrEngine(ptrEngine)
{
	clickX = x;
	clickY = y;
	setVisible(true);
}

HitMarker::~HitMarker(void)
{
}

/**
	Class: MovingText
	Function: virtDraw()
	Description: This is used to display the elements within strvec on the screen.
*/

void HitMarker::virtDraw()
{

	ptrEngine->drawBackgroundLine(clickX - 10, clickY, clickX + 10, clickY, 0xFFFFFF);
	//Vertical
	ptrEngine->drawBackgroundLine(clickX, clickY - 10, clickX, clickY + 10, 0xFFFFFF);

	
}

/**
	Class: MovingText
	Function: virtDoUpdate()
	Description: This is used to commence the movement of the string
				 using the MovementPosition object.
*/
void HitMarker::virtDoUpdate(int iCurrentTime)
{
	if (ptrEngine->getMouseLifted()) {
		ptrEngine->drawBackgroundLine(clickX - 10, clickY, clickX + 10, clickY, 0x000000);
		//Vertical
		ptrEngine->drawBackgroundLine(clickX, clickY - 10, clickX, clickY + 10, 0x000000);
	}
}

