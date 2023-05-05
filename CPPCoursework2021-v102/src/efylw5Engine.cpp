#include "efylw5Engine.h"
/**
	Class: efylw5Engine
	Function: deleteName()
	Description: This will be called in the main menu when the user press the backspace key,
				 which will delete the last character of the name string. It will not be activated
				 if the length of the name is 0.
*/

void efylw5Engine::deleteName()
{
	if (name.length() != 0)
	{
		name.pop_back();
	}
}

void efylw5Engine::deleteHiddenMessage()
{
	if (hiddenMessage.length() != 0)
	{
		hiddenMessage.pop_back();
	}
}

/**
	Class: efylw5Engine
	Function: drawTable()
	Description: This function will be called alongside with populateTable()
				 by virtSetupBackgroundBuffer().It basically draws the frame 
				 of the table without populating it with data.
*/
void efylw5Engine::drawTable()
{
	drawBackgroundRectangle(348, 180, 990, 250, 0xFFFFFF);
	drawBackgroundRectangle(378, 190, 960, 240, 0x000000);
	drawBackgroundRectangle(348, 250, 990, 320, 0xFFFFFF);
	drawBackgroundRectangle(378, 260, 960, 310, 0x000000);
	drawBackgroundRectangle(348, 320, 990, 390, 0xFFFFFF);
	drawBackgroundRectangle(378, 330, 960, 380, 0x000000);
	drawBackgroundRectangle(348, 390, 990, 460, 0xFFFFFF);
	drawBackgroundRectangle(378, 400, 960, 450, 0x000000);
	drawBackgroundRectangle(348, 460, 990, 530, 0xFFFFFF);
	drawBackgroundRectangle(378, 470, 960, 520, 0x000000);
	drawBackgroundRectangle(348, 530, 990, 600, 0xFFFFFF);
	drawBackgroundRectangle(378, 540, 960, 590, 0x000000);
	drawBackgroundRectangle(655, 180, 699, 600, 0xFFFFFF);
}

/**
	Class: efylw5Engine
	Function: populateTable()
	Description: This function will be called alongside with drawTable().
				 It is responsible for populating the table with data such 
				 as player's name and score.
*/
void efylw5Engine::populateTable()
{
	char buf[124];
	//Populate the highscore table
	std::vector<std::pair<std::string, int>> res = getCurrentState()->getScores();
	if (res.size() == 0)
		return;
	int x = 460, y = 270;
	//Only display top 5
	for (int i = 0; i < 5; ++i) {
		sprintf(buf, res[i].first.c_str());
		drawForegroundString(x, y, buf, 0xFFFFFF, NULL);
		x += 350;
		sprintf(buf, std::to_string(res[i].second).c_str());
		drawForegroundString(x, y, buf, 0xFFFFFF, NULL);
		x -= 350;
		y += 70;
	}
}

void efylw5Engine::drawCredit()
{
	m_iDefaultUpdatePeriod = 50;
	fillBackground(0);
	char buf[128];
	sprintf(buf, "Credit");
	drawBackgroundString(600, 100, buf, 0x0000FF, NULL);
	sprintf(buf, "Project Manager: Brax");
	drawBackgroundString(475, 200, buf, 0x0000FF, NULL);
	sprintf(buf, "Software Developer: Brax");
	drawBackgroundString(450, 300, buf, 0x0000FF, NULL);
	sprintf(buf, "Quality Assurance Member: Brax");
	drawBackgroundString(410, 400, buf, 0x0000FF, NULL);
	sprintf(buf, "Thank You For Playing Sharp Shooter!");
	drawBackgroundString(360, 500, buf, 0x0000FF, NULL);
	SimpleImage image = ImageManager::loadImage("smileEmote.png", true);
	image.renderImage(this->getBackgroundSurface(), 0, 0, 925, 440, 155, 155);
	sprintf(buf, "Press Escape to return to the main menu");
	drawBackgroundString(340, 600, buf, 0x0000FF, NULL);
}


void efylw5Engine::virtSetupBackgroundBuffer()
{
	if (getCurrentState()->getState() == 6) 
	{
		drawTable();
	}
	else if (getCurrentState()->getState() == 1)
	{
		SimpleImage image = ImageManager::loadImage(getCurrentState()->getImageURL(), true);
		image.renderImage(this->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
		drawBackgroundRectangle(350, 600, 550, 650, 0x0000FF);
		drawBackgroundRectangle(750, 600, 950, 650, 0x0000FF);
	}
	else if (getCurrentState()->getState() == 7)
	{
		drawCredit();
	}
	else 
	{
		SimpleImage image = ImageManager::loadImage(getCurrentState()->getImageURL(), true);
		image.renderImage(this->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
	}

}


void efylw5Engine::copyAllBackgroundBuffer()
{
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
	if(getCurrentState()->getState() != 7)
		m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, 0);
}

void efylw5Engine::virtMainLoopDoBeforeUpdate()
{
	if(getCurrentState()->getState() == 7)
		m_iOffset = (m_iOffset + 1) % getWindowHeight();
		this->redrawDisplay();
}

void efylw5Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
}

void efylw5Engine::virtMouseDown(int iButton, int iX, int iY)
{

	switch (iButton)
	{
	case 2: // Middle
		if(getCurrentState()->getState() == 5)
			zooming.compress();
		break;
	case 3: // Right
		if (getCurrentState()->getState() == 5)
			zooming.stretch();
		break;
	}
	if (getCurrentState()->getState() == 1 || getCurrentState()->getState() == 3)
	{
		drawBackgroundLine(iX - fr.getCrosshairSize(), iY, iX + fr.getCrosshairSize(), iY, fr.getCrosshairColor());
		drawBackgroundLine(iX, iY - fr.getCrosshairSize(), iX, iY + fr.getCrosshairSize(), fr.getCrosshairColor());
		setClickX(iX);
		setClickY(iY);
		mouseLifted = false;
		if (getCurrentState()->getState() == 1)
		{
			if ((iX >= 350 && iX <= 550) && (iY >= 600 && iY <= 650))
			{
				destroyOldObjects(true);
				efylw5Engine::setCurrentState(new creditState(this));
				setState(7);
				lockAndSetupBackground();
				redrawDisplay();
			}
			else if ((iX >= 750 && iX <= 950) && (iY >= 600 && iY <= 650))
			{
				destroyOldObjects(true);
				efylw5Engine::setCurrentState(new tutorialState());
				setState(2);
				lockAndSetupBackground();
				redrawDisplay();
			}
		}
	}
	else if (getCurrentState()->getState() == 4)
	{
		if ((iX >= 640 && iX <= 750) && (iY >= 640 && iY <= 650))
		{
			destroyOldObjects(true);
			efylw5Engine::setCurrentState(new creditState(this));
			setState(7);
			lockAndSetupBackground();
			redrawDisplay();
		}
	}
	else {
		return;
	}
}

void efylw5Engine::virtMouseUp(int iButton, int iX, int iY)
{
	if (getCurrentState()->getState() == 1 || getCurrentState()->getState() == 3)
		drawBackgroundLine(getClickX() - 10, getClickY(), getClickX() + 10, getClickY(), 0x000000);
		drawBackgroundLine(getClickX(), getClickY() - 10, getClickX(), getClickY() + 10, 0x000000);
		lockAndSetupBackground();
		redrawDisplay();
		mouseLifted = true;

}


void efylw5Engine::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) 
	{
		case SDLK_a:
			if (getCurrentState()->getState() == 1)
			{
				setName("a");
			}
			else if(getCurrentState()->getState() == 5)
			{
				setHiddenMessage("a");
			}
			break;
		case SDLK_b:
			if (getCurrentState()->getState() == 1)
			{
				setName("b");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("b");
			}
			break;
		case SDLK_c:
			if (getCurrentState()->getState() == 1)
			{
				setName("c");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("c");
			}
			break;
		case SDLK_d:
			if (getCurrentState()->getState() == 1)
			{
				setName("d");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("d");
			}
			break;
		case SDLK_e:
			if (getCurrentState()->getState() == 1)
			{
				setName("e");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("e");
			}
			break;
		case SDLK_f:
			if (getCurrentState()->getState() == 1)
			{
				setName("f");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("f");
			}
			break;
		case SDLK_g:
			if (getCurrentState()->getState() == 1)
			{
				setName("g");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("g");
			}
			break;
		case SDLK_h:
			if (getCurrentState()->getState() == 1)
			{
				setName("h");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("h");
			}
			break;
		case SDLK_i:
			if (getCurrentState()->getState() == 1)
			{
				setName("i");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("i");
			}
			break;
		case SDLK_j:
			setName("j");
			break;
		case SDLK_k:
			if (getCurrentState()->getState() == 1)
			{
				setName("k");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("k");
			}
			break;
		case SDLK_l:
			if (getCurrentState()->getState() == 1)
			{
				setName("l");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("l");
			}
			break;
		case SDLK_m:
			if (getCurrentState()->getState() == 1)
			{
				setName("m");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("m");
			}
			break;
		case SDLK_o:
			if (getCurrentState()->getState() == 1)
			{
				setName("o");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("o");
			}
			break;
		case SDLK_q:
			if (getCurrentState()->getState() == 1)
			{
				setName("q");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("q");
			}
			break;
		case SDLK_r:
			if(getCurrentState()->getState() == 6){
				this->name = "";
				storeObjectInArray(0, new SnakeHead(this, 10, 10, 125, 0, 125, 800, nullptr));
				storeObjectInArray(1, new SnakeHead(this, 30, 30, 1175, 0, 1175, 800, nullptr));
				efylw5Engine::setCurrentState(new startingState(this));
				setState(1);
				lockAndSetupBackground();
				redrawDisplay();
			}
			else {
				if (getCurrentState()->getState() == 1)
				{
					setName("r");
				}
				else if (getCurrentState()->getState() == 5)
				{
					setHiddenMessage("r");
				}
			}
			break;
		case SDLK_s:
			if (getCurrentState()->getState() == 1)
			{
				setName("s");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("s");
			}
			break;
		case SDLK_t:
			if (getCurrentState()->getState() == 1)
			{
				setName("t");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("t");
			}
			break;
		case SDLK_u:
			if (getCurrentState()->getState() == 1)
			{
				setName("u");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("u");
			}
			break;
		case SDLK_v:
			if (getCurrentState()->getState() == 1)
			{
				setName("v");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("v");
			}
			break;
		case SDLK_w:
			if (getCurrentState()->getState() == 1)
			{
				setName("w");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("w");
			}
			break;
		case SDLK_x:
			if (getCurrentState()->getState() == 1)
			{
				setName("x");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("x");
			}
			break;
		case SDLK_y:
			if (getCurrentState()->getState() == 1)
			{
				setName("y");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("y");
			}
			break;
		case SDLK_z:
			if (getCurrentState()->getState() == 1)
			{
				setName("z");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("z");
			}
			break;
		case SDLK_0:
			if (getCurrentState()->getState() == 1)
			{
				setName("0");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("0");
			}
			break;
		case SDLK_1:
			if (getCurrentState()->getState() == 1)
			{
				setName("1");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("1");
			}
			break;
		case SDLK_2:
			if (getCurrentState()->getState() == 1)
			{
				setName("2");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("2");
			}
			break;
		case SDLK_3:
			if (getCurrentState()->getState() == 1)
			{
				setName("3");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("3");
			}
			break;
		case SDLK_4:
			if (getCurrentState()->getState() == 1)
			{
				setName("4");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("4");
			}
			break;
		case SDLK_5:
			if (getCurrentState()->getState() == 1)
			{
				setName("5");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("5");
			}
			break;
		case SDLK_6:
			if (getCurrentState()->getState() == 1)
			{
				setName("6");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("6");
			}
			break;
		case SDLK_7:
			if (getCurrentState()->getState() == 1)
			{
				setName("7");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("7");
			}
			break;
		case SDLK_8:
			if (getCurrentState()->getState() == 1)
			{
				setName("8");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("8");
			}
			break;
		case SDLK_9:
			if (getCurrentState()->getState() == 1)
			{
				setName("9");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("9");
			}
			break;
		case SDLK_BACKSPACE:
			if (getCurrentState()->getState() == 1)
			{
				deleteName();
			}
			else if (getCurrentState()->getState() == 5)
			{
				deleteHiddenMessage();
			}
			break;
		case SDLK_RETURN:
			std::cout << getName() << "\n";
			//Avoid going back to the tutorial page
			if (getCurrentState()->getState() == 1) {
				if (getName() == "") {
					setName("Unknown");
				}
				addPlayerName();
				setReturnToTutorial(false);
				destroyOldObjects(true);
				efylw5Engine::setCurrentState(new tutorialState());
				setState(3);
				lockAndSetupBackground();
				redrawDisplay();
			}
			else if (getCurrentState()->getState() == 5)
			{
				if (getHiddenMessage() == "ng15en")
				{
					setPoint(getPoint() + 100);
					destroyOldObjects(true);
					appendObjectToArray(new HSObjectL(this, 20, 20, 200, 100, 0, 50));
					appendObjectToArray(new HSObjectR(this, 20, 20, 1020, 100, 1220, 50));
					appendObjectToArray(new MovingText(this, 20, 20, 1020, 100, 1220, 50));
					efylw5Engine::setCurrentState(new highscoreState(this));
					setState(6);
					lockAndSetupBackground();
					redrawDisplay();
				}
				else
				{
					std::cout << getHiddenMessage() << "\n";
				}
			}
			break;
		case SDLK_ESCAPE:
			if (getCurrentState()->getState() == 7) 
			{
				this->name = "";
				storeObjectInArray(0, new SnakeHead(this, 10, 10, 125, 0, 125, 800, nullptr));
				storeObjectInArray(1, new SnakeHead(this, 30, 30, 1175, 0, 1175, 800, nullptr));
				m_iDefaultUpdatePeriod = 10;
				efylw5Engine::setCurrentState(new startingState(this));
				setState(1);
				lockAndSetupBackground();
				redrawDisplay();
			}
			else
			{
				//In case users quit before it got to append the score
				if (!timer->getAppended())
				{
					timer->appendPointsToFile();
				}
				virtCleanUp();
				setExitWithCode(1);

			}
			break;
		case SDLK_SPACE:
			//Avoid multiple snakeObject from spawning without gaining a point and make sure you can't skip the tutorial state
			if (getCurrentState()->getState() == 2) {
				timer = new Timer(this, fr.getTimeLimit());
				setReturnToGame(false);
				efylw5Engine::setCurrentState(new runningState(this));
				appendObjectToArray(timer);
				appendObjectToArray(new Spawner(this, timer, fr.getColor10(), fr.getColor20(), fr.getColor100(), fr.getDifficulty(), fr.getTargetShapes()));
				setState(3);
				lockAndSetupBackground();
				redrawDisplay();
			}
			break;
		case SDLK_p:
			if (getCurrentState()->getState() == 1) {
				setName("p");
			}
			//Make sure users can only pause the system in runningState
			if (getCurrentState()->getState() == 3) {
				if (isPaused()) {
					unpause();
				}
				else {
					pause();
				}
			}
			break;
		case SDLK_n:;
			if (getCurrentState()->getState() == 1)
			{
				setName("n");
			}
			else if (getCurrentState()->getState() == 5)
			{
				setHiddenMessage("n");
			}
			break;
		case SDLK_LEFT:
			if(getCurrentState()->getState() == 5)
				scrolling.changeOffset(10, 0);
			redrawDisplay();
			break;
		case SDLK_RIGHT:
			if (getCurrentState()->getState() == 5)
				scrolling.changeOffset(-10, 0);
			redrawDisplay();
			break;
		case SDLK_UP:
			if (getCurrentState()->getState() == 5)
				scrolling.changeOffset(0, 10);
			redrawDisplay();
			break;
		case SDLK_DOWN:
			if (getCurrentState()->getState() == 5)
				scrolling.changeOffset(0, -10);
			redrawDisplay();
			break;


	}
	
}
/**
	Class: efylw5Engine
	Function: addPlayerName()
	Description: This will create an ofstream object, then open or create a file called Player.txt
				 make sure the open mode is append, then get the value of name and write to the file.
				 Then closing the ofstream object
*/
void efylw5Engine::addPlayerName()
{
	std::ofstream os;
	os.open("Player.txt", std::ios::app);
	os << getName() << "\n";
	os.close();
}

void efylw5Engine::virtDrawStringsUnderneath()
{
	if (getCurrentState()->getState() != 7) {
		char str[128];
		char buf[128];
		if (getCurrentState()->getState() == 5)
		{
			
			for (int i = 0; i < getCurrentState()->getStr().size(); ++i) {
				if (i == 2)
				{
					FontManager f;
					sprintf(str, getCurrentState()->getStr()[i]);
					f.loadFonts();
					drawForegroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, f.getFont("Cornerstone Regular.ttf", 8));
					
				}
				else
				{
					sprintf(str, getCurrentState()->getStr()[i]);
					drawForegroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, NULL);
				}
			}
			if (getHiddenMessage() != "")
				sprintf(buf, getHiddenMessage().c_str());
				drawForegroundString(600, 700, buf, 0xeae7db, NULL);
		}
		else
		{
			if (getCurrentState()->getState() == 4)
			{
				sprintf(str, std::to_string(getPoint()).c_str());
				drawForegroundString(760, 401, str, 0xeae7db, NULL);
			}
			for (int i = 0; i < getCurrentState()->getStr().size(); ++i) 
			{
				sprintf(str, getCurrentState()->getStr()[i]);
				drawForegroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, NULL);
			}
			if (name != "" && getCurrentState()->getState() == 1) 
			{
				sprintf(str, getName().c_str());
				drawForegroundString(600, 500, str, 0xeae7db, NULL);
			}
		}
	}
	
}

void efylw5Engine::virtDrawStringsOnTop()
{

	if (getCurrentState()->getState() != 7) {
		char buf[128];
		if (isPaused()) {
			sprintf(buf, "Press p to unpause");
			drawForegroundString(525, 360, buf, 0x00ffff, NULL);
		}
		if (getCurrentState()->getState() == 6) {
			populateTable();
		}
	}
}

void efylw5Engine::virtCleanUp()
{
	DisplayableObject* objPtr;

	for (int iObjectId = 0; (objPtr = getDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		if (objPtr == nullptr)
			continue;
		else {
			delete(objPtr);
		}
	}
}

int efylw5Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();

	destroyOldObjects(true);

	createObjectArray(2);
	
	storeObjectInArray(0, new SnakeHead(this,10,10, 125, 0, 125, 800, nullptr));

	storeObjectInArray(1, new SnakeHead(this,30,30, 1175, 0, 1175, 800, nullptr));

	setAllObjectsVisible(true);

	return 0;
}

int efylw5Engine::virtInitialise()
{
	getBackgroundSurface()->setDrawPointsFilter(&scrolling);
	getForegroundSurface()->setDrawPointsFilter(&scrolling);

	return BaseEngine::virtInitialise();
}




