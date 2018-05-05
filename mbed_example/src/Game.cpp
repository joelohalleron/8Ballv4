#include "Game.h"




Player::Player() {
	p_id = 1;
	final = false;
	total_balls = 7;
	previous_total_balls = 7;
}

Player::Player(int id, int total) {
	p_id = id;
	final = false;
	total_balls = total;
	previous_total_balls = total;
}

Game::Game() {
	P1 = Player(1,7);
	P2 = Player(1,7);
	currentPlayer = 1;
	initializeGame();
}

Game::Game(Display* screen) {
	Interface i = Interface(screen);
	interface = i;
	P1 = Player(1,7);
	P2 = Player(1,7);
	currentPlayer = 1;
	initializeGame();
}


void Game::initializeGame() {

	currentPlayer = 1;
	cueBall_collided = false;
	mode = DIRECTION;

	ba.initializeBallArray(NUM_BALLS);

	cueBall = ba.getBall(0);
	blackBall = ba.getBall(8);

	interface.setBallsArray(&ba);
	interface.setCueBall(cueBall);
	interface.setBlackBall(blackBall);
	interface.setTable(&table);
	
	//Initialise the interface
	interface.init();
}

void Game::draw() {
	interface.init();
	interface.drawTable();
	interface.drawBalls();
	interface.playerTurn(currentPlayer);
	interface.drawShotStrength(strength);
}

void Game::drawShot() {
	interface.drawCue(&shot, true);
}

void Game::drawSelection() {
	interface.drawCue(&shot, false);
}

bool Game::isOver() {
	Ball* b;
	for (int i = 1; i < ba.getSize(); i++) {
		b = ba.getBall(i);
		if (b->inGame()) {
			return false;
		}
	}
	return true;
}

bool Game::turnEnded() {
	Ball* b;
	int i;
	for (i = 0; i < ba.getSize(); i++) {
		b = ba.getBall(i);
		if (b->inGame()) {
			if (b->isMoving()) {
				return false;
			}
		}
	}
	processEnd();
	currentPlayer = op_id(currentPlayer);
	interface.playerTurn(currentPlayer);
	cueBall_collided = false;
	return true;
	};


void Game::processEnd() {
	bool illegalMovePlayer1 = illegalMove(1);
	bool illegalMovePlayer2 = illegalMove(2);

	updateBallCount();
	
	if (currentPlayer == 1) {
		if (illegalMovePlayer1) {
			interface.drawIllegalMove(P1.p_id);
			
			
			// Ball count can be left alone as killPlayerBall deals with it
			killPlayerBall(2);
			respawnCueBall();
			
			// if player 2 is out of balls now
			if (P2.total_balls == 0) {
				processEndGame(2);
			}

		}
		if (!ba.getBall(8)->inGame()) {
			if (P1.total_balls == 0) {
				processEndGame(1);
			} else {
				processEndGame(2);
			}
		}
	}
	if (currentPlayer == 2) {
		if (illegalMovePlayer2) {
			interface.drawIllegalMove(P2.p_id);;

			// Ball count can be left alone as killPlayerBall deals with it
			killPlayerBall(1);
			respawnCueBall();

			// if player 1 is out of balls now
			if (P1.total_balls == 0) {
				processEndGame(1);
			}
		}
		if (!ba.getBall(8)->inGame()) {
			if (P2.total_balls == 0) {
				processEndGame(2);
			} else {
				processEndGame(1);
			}
		}

	}

	// Make sure a player who potted can keep playing

	// Check if it was player one who hit one or more balls 
	if (P1.total_balls < P1.previous_total_balls) {
		// Quick fix to continue playing Player 1
		if (!illegalMovePlayer1) {
			currentPlayer = op_id(currentPlayer);
		}
	}
	// Update the number of balls
	P1.previous_total_balls = P1.total_balls;
	
	// Check if it was player 2 who hit one or more balls
	if (P2.total_balls < P2.previous_total_balls) {
		// Quick fix to continue playing Player 2
		if (!illegalMovePlayer2) {
			currentPlayer = op_id(currentPlayer);
		}
	}
	// atualiza o numero de bolas anterior
	P2.previous_total_balls = P2.total_balls;

}

// update ball count for both players
void Game::updateBallCount() {
	Ball* b;
	int balls1 = 0;
	int balls2 = 0;
	for (int i = 1; i < 16; i++) {
		b = ba.getBall(i);
		if (b->inGame()){
			if (i < 8)
				balls1++;
			if (i > 8)
				balls2++;
		}
	}
	
	P1.total_balls = balls1;
	P2.total_balls = balls2;
}

bool Game::illegalMove(int pl) {
	if (!cueBall_collided) {
		return true;
	}
	if (pl == 1) {
		if ( (ball_hit > 8)  || 
				((ball_hit == 8) && (P1.total_balls != 0)) ) {
			return true;
		}
	}
	if (pl == 2) {
		if ( (ball_hit < 8)  || 
				((ball_hit == 8) && (P2.total_balls != 0)) ) {
			return true;
		}
	}
	return false;
}



void Game::killPlayerBall(int pl) {
	int minBall = 1, maxBall = 7;
	// Balls 9 and 16
	if (pl == 2) {
		minBall = 9;
		maxBall = 15;
	}
	Ball* b;
	for (int i = minBall; i <= maxBall; i++) {
		b = ba.getBall(i);
		if (b->inGame()) {

			b->kill();
			if (pl == 1) {
				P1.total_balls--;
				P1.previous_total_balls--;
			}
			if (pl == 2) {
				P2.total_balls--;
				P2.previous_total_balls--;
			}
			return;
		}
	}
}

void Game::processEndGame(int pl) {
	mode = FIM;
	interface.playerWon(pl);
}

bool Game::checkCueBall() {
	if (!cueBall->inGame()) {
		respawnCueBall();
		return true;
	}
	return false;
}

void Game::respawnCueBall() {

	shot.setAngle(90.0);
	cueBall->whitePosition();
	cueBall->putInGame();

	physics.respawnCollision(&table, &ba, true);
	drawSelection();

	cueBall->setYPosition((int) cueBall->getZPosition());
}

void Game::physicsInterface() {

	int i;
	Ball* myBall;
	Ball* otherBall;

	for (i = 0; i < ba.getSize(); i++) {

		myBall = ba.getBall(i);

		if (myBall->inGame()) {
			physics.movement(myBall);

			physics.holeAreaCollision(&table, myBall);

			physics.tableCollision(&table, myBall);

			physics.getCollisionOrder(&ba, i);
			
			while (physics.hasCollisions()) {
				otherBall = ba.getBall(physics.getCollision());
				physics.ballCollision(myBall, otherBall);
				if ((myBall == cueBall) and (!cueBall_collided)) {
					ball_hit = otherBall->getNumber();
					cueBall_collided = true;
				}
			}
		}

	}
			
}


int Game::op_id(int pl) {
	if (pl == 1)
		return 2;
	return 1;
}

void Game::setDirection(btnId_t b) {
	switch (b) {
	case JUP:
		shot.addAngle(2.0);
		//updateShot();
		interface.drawCue(&shot, true);
		break;
	case JDN:
		shot.addAngle(-2.0);
		//updateShot();
	  interface.drawCue(&shot, true);
		break;
	case JRT:
		shot.addAngle(2);
		//updateShot();
	  interface.drawCue(&shot, true);
		break;
	case JLT:
		shot.addAngle(-2);
	  //updateShot();
	  interface.drawCue(&shot, true);
	  
		break;
	case JCR:
		updateShot();
		executeShot();
		break;
	default:
		break;
	}
}

void Game::setStrength(float s)
{
	this->strength = s;
	updateShot();
}

void Game::updateShot() {
	strLevel = 5;
	strength*=strLevel;
	shot.setStr(strength);
}

void Game::executeShot() {
		physics.hitCueBall(cueBall, &shot);
		mode = PHYSICS;
}

void Game::applyPhysics() {
	if (physicsTimer.elapsed() < 0.007)
		return;
	physicsTimer.start();
	if (!turnEnded()) {
		physicsInterface();
	} else {
		if(isOver()){
			if (mode != FIM)
				initializeGame();
		}
		else {
			if (mode != FIM)
				mode = DIRECTION;
		}
	}
}

void Game::loop() {
	switch (mode) {		
	case DIRECTION:
		checkCueBall();
		drawShot();
		break;
	case PHYSICS:
		applyPhysics();
		break;
	default:
		break;
	}
}



void Game::processKey(btnId_t b) {

	/*if (b == JCR)
	{initializeGame();}*/
	switch (mode) {
	case DIRECTION:
		setDirection(b);
		break;
	default:
		break;
	}
}

void Game::SetDisplay(Display *screen)
{
	this->screen = screen;
}



