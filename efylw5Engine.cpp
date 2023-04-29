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

void efylw5Engine::setUpForegroundEffectHS()
{
	
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
void efylw5Engine::virtSetupBackgroundBuffer()
{
	
	if (getCurrentState()->getState() == 6) {
		drawTable();
	
	}
	else {
		SimpleImage image = ImageManager::loadImage(getCurrentState()->getImageURL(), true);
		image.renderImage(this->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);
	}

}


void efylw5Engine::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode) 
	{
		case SDLK_a:
			setName("a");
			break;
		case SDLK_b:
			setName("b");
			break;
		case SDLK_c:
			setName("c");
			break;
		case SDLK_d:
			setName("d");
			break;
		case SDLK_e:
			setName("e");
			break;
		case SDLK_f:
			setName("f");
			break;
		case SDLK_g:
			setName("g");
			break;
		case SDLK_h:
			setName("h");
			break;
		case SDLK_i:
			setName("i");
			break;
		case SDLK_j:
			setName("j");
			break;
		case SDLK_k:
			setName("k");
			break;
		case SDLK_l:
			setName("l");
			break;
		case SDLK_m:
			setName("m");
			break;
		case SDLK_o:
			setName("o");
			break;
		case SDLK_q:
			setName("q");
			break;
		case SDLK_r:
			if(getCurrentState()->getState() == 6){
				storeObjectInArray(0, new SnakeHead(this, 10, 10, 125, 0, 125, 800, nullptr));
				storeObjectInArray(1, new SnakeHead(this, 30, 30, 1175, 0, 1175, 800, nullptr));
				efylw5Engine::setCurrentState(new startingState(this));
				setState(1);
				lockAndSetupBackground();
				redrawDisplay();
			}
			else {
				setName("r");
			}
			break;
		case SDLK_s:
			setName("s");
			break;
		case SDLK_t:
			setName("t");
			break;
		case SDLK_u:
			setName("u");
			break;
		case SDLK_v:
			setName("v");
			break;
		case SDLK_w:
			setName("w");
			break;
		case SDLK_x:
			setName("x");
			break;
		case SDLK_y:
			setName("y");
			break;
		case SDLK_z:
			setName("z");
			break;
		case SDLK_BACKSPACE:
			deleteName();
			break;
		case SDLK_RETURN:
			std::cout << getName() << "\n";
			//Avoid going back to the tutorial page
			if (returnToTutorial) {
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
			break;
		case SDLK_ESCAPE:
			destroyOldObjects(true);
			setExitWithCode(1);
		case SDLK_SPACE:
			//Avoid multiple snakeObject from spawning without gaining a point and make sure you can't skip the tutorial state
			if (returnToGame && getCurrentState()->getState() == 2) {
				setReturnToGame(false);
				FoodObject* fo = new FoodObject(this, 300, 300, 200, 220, 200, 220);
				so = new SnakeHead(this, 30, 30, 10, 10, 1290, 10,fo);
				appendObjectToArray(fo);
				this->setSnakeHead(so);
				efylw5Engine::setCurrentState(new runningState(this->so,this));
				setState(3);
				appendObjectToArray(so);
				lockAndSetupBackground();
				redrawDisplay();
			}
			break;
		case SDLK_LSHIFT:
			if (getCurrentState()->getState() != 1)
			{
				efylw5Engine::setCurrentState(new winningState());
				setState(4);
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
		case SDLK_n:
			if (getCurrentState()->getState() == 1) {
				setName("n");
			}
			else {
				SnakeBody* sb = new SnakeBody(this, so, 40, 40, 0, 0, 0, 0, 1);
				appendObjectToArray(sb);
				std::vector<SnakeBody*> sc = so->getSnakeBodyCoords();
				sc.push_back(sb);
				so->setSnakeBodyCoords(sc);
				so->setBodyCount(so->getBodyCount() + 1);
			}
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

	char str[128];
	for (int i = 0; i < getCurrentState()->getStr().size(); ++i) {
		sprintf(str, getCurrentState()->getStr()[i]);
		drawForegroundString(getCurrentState()->getCoordX()[i], getCurrentState()->getCoordY()[i], str, 0xeae7db, NULL);
	}
	if (name != "" && getCurrentState()->getState() == 1) {

		sprintf(str, getName().c_str());
		drawForegroundString(600, 500, str, 0xeae7db, NULL);
	}
	
}

void efylw5Engine::virtDrawStringsOnTop()
{
	char buf[128];
	if (isPaused()) {
		sprintf(buf, "Press p to unpause");
		drawForegroundString(525, 360, buf, 0x00ffff, NULL);
	}
	if (getCurrentState()->getState() == 6) {
		populateTable();
		setUpForegroundEffectHS();
	}
}

int efylw5Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();

	destroyOldObjects(true);

	createObjectArray(6);
	
	if(getCurrentState()->getState() == 1)
	{
		storeObjectInArray(0, new SnakeHead(this,10,10, 125, 0, 125, 800, nullptr));

		storeObjectInArray(1, new SnakeHead(this,30,30, 1175, 0, 1175, 800, nullptr));
	}
	else if(getCurrentState()->getState() == 6)
	{
		this->setName("Brax");

		storeObjectInArray(2, new HSObjectL(this,20,20,200,100,0,50));

		storeObjectInArray(3, new HSObjectR(this,20,20,1020,100,1220,50));

		storeObjectInArray(4, new MovingText(this, 20, 20, 1020, 100, 1220, 50));
	}

	setAllObjectsVisible(true);

	return 0;
}




