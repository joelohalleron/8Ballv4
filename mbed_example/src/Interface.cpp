

#include "Interface.h"



Interface::Interface() {
}

Interface::~Interface() {
}

Interface::Interface(Display* screen)
{
	this->screen = screen;
}


void Interface::init() {

	// Initialise the display
  screen->fillScreen(WHITE);
  screen->setTextColor(BLACK, WHITE);
	
	/*Ball* b;
	for (int i = 0; i < ba->getSize(); i++) {
		b = ba->getBall(i);
		b->draw(screen, RED);
	}*/

}

void Interface::drawTable()
{
	table->draw(screen);
}

void Interface::drawBalls() {
	Ball* b;

	for (int i = 0; i < ba->getSize(); i++) {
		b = ba->getBall(i);
		if (b->inGame())
		{
			switch (i) {
				case 0: b->draw(screen, WHITE);
				break;
				
				case 8: b->draw(screen, BLACK);
				break;
			}
				if(i != 0)
				{
					if(i<8)
					{
						b->draw(screen, RED);
					}
					else {if(i>8){b->draw(screen, YELLOW);}}
			}
		}
	}
}

void Interface::drawCue(Shot* shot, bool guideLine) {
	cue.setPosition(cueBall->getPosition());
	cue.setAngle(shot->getAngle());
	cue.setStrength(shot->getStr());
	cue.draw(screen, shot, ba->getWhitePosition());
}

void Interface::drawShotStrength(float s)
{
		screen->setCursor(5,0);
		screen->printf("Shot strength : %f", s);
}

void Interface::drawIllegalMove(int player)
{
	screen->setCursor(5, 255);
	screen->printf("                                                           ");
	if(player == 1)
	screen->printf("Illegal move from Player 1! Player 2 has one ball less.");
	else
	screen->printf("Illegal move from Player 2! Player 1 has one ball less.");
}

void Interface::playerTurn(int pID)
{
	screen->setCursor(130, 0);
	screen->printf("                ");

	screen->printf("Player %d turn", pID);

}

void Interface::playerWon(int pID)
{
	screen->setCursor(0, 100);
	screen->printf("                                                           ");
	if(pID == 1)
	screen->printf("Congratulations Player %d ! You Won!.",pID);

}


Table *Interface::getTable() const {
	return table;
}

void Interface::setTable(Table *table) {
	this->table = table;
}

Ball *Interface::getCueBall() const {
	return cueBall;
}

void Interface::setCueBall(Ball *cueBall) {
	this->cueBall = cueBall;
}

Ball *Interface::getBlackBall() const {
	return blackBall;
}

void Interface::setBlackBall(Ball *blackBall) {
	this->blackBall = blackBall;
}

BallArray *Interface::getBallsArray() const {
	return ba;
}

void Interface::setBallsArray(BallArray *ba) {
	this->ba = ba;
}

