
#include "Ball.h"



bool Ball::inGame() {
	return (gameStatus);
}

void Ball::draw(Display* screen, uint16_t colour)
{
	screen->fillCircle(getXPosition(),getZPosition(),BALL_RADIUS, colour);
}

int Ball::getNumber() {
	return (number);
}

Vector Ball::getPosition() {
	return (center);
}

float Ball::getXPosition() {
	return (center.getX());
}

float Ball::getZPosition() {
	return (center.getZ());
}

Vector Ball::getSpeed() {
	return (speed);
}

float Ball::getXSpeed() {
	return (speed.getX());
}

float Ball::getYSpeed() {
	return (speed.getZ());
}

float Ball::getLastAngle() {
	return (speedAngle);
}

void Ball::setPosition(Vector* v) {
	center.setVector(v);
}

void Ball::setXPosition(float x) {
	center.setX(x);
}

void Ball::setYPosition(float y) {
	center.setZ(y);
}

void Ball::setSpeed(Vector* v) {
	speed.setVector(v);
}

void Ball::addPosition(Vector* v) {
	center.addVector(v);
}

void Ball::addXPosition(float value) {
	Vector v(value, 0.0);
	center.addVector(&v);
}

void Ball::addYPosition(float value) {
	Vector v(0.0, value);
	center.addVector(&v);
}

void Ball::subPosition(Vector* v) {
	center.subVector(v);
}

void Ball::subXPosition(float value) {
	Vector v(value, 0.0);
	center.subVector(&v);
}

void Ball::subYPosition(float value) {
	Vector v(0.0, value);
	center.subVector(&v);
}

bool Ball::isMoving() {
	return (speed.getX() != 0.0 || speed.getZ() != 0.0);
}

float Ball::calculateSpeedAngle() {
	Vector v;
	speedAngle = v.calculateAngle(&speed);
	return (speedAngle);
}

void Ball::resetSpeed() {
	speed.setVector(0.0, 0.0);
}

void Ball::addSpeed(Vector* v) {
	speed.addVector(v);
}

void Ball::subSpeed(Vector* v) {
	speed.subVector(v);
}

void Ball::rotateSpeed(float angle) {
	speed.vectorRotation(angle);
}

void Ball::tradeXSpeed(Ball* b) {
	Vector aux1(b->getXSpeed(), getYSpeed());
	Vector aux2(getXSpeed(), b->getYSpeed());

	setSpeed(&aux1);
	b->setSpeed(&aux2);
}

void Ball::tradeYSpeed(Ball* b){
	Vector aux1(getXSpeed(), b->getYSpeed());
	Vector aux2(b->getXSpeed(), getYSpeed());
	
	setSpeed(&aux1);
	b->setSpeed(&aux2);
}

void Ball::reverseXSpeed() {
	Vector aux(-1.0, 1.0);
	speed.mulVector(&aux);
}

void Ball::reverseZSpeed() {
	Vector aux(1.0, -1.0);
	speed.mulVector(&aux);
}

void Ball::putInGame() {
	gameStatus = true;
}

void Ball::kill() {
	gameStatus = false;
}

void Ball::whitePosition() {
	Vector defaultPosition(CENTER_X - 90, CENTER_Z);
	setPosition(&defaultPosition);
}

void Ball::blackPosition() {
	Vector defaultPosition(BLACK_X_START, BLACK_Z_START);
	setPosition(&defaultPosition);
}

//Ball Array member functions

void BallArray::initializeBallArray(int totalBalls) {
	int i, Row;
	int player, p1 = 1, p2 = 9;
	size = totalBalls;

	for (i = 0; i < size; i++) {
		array[i].number = i;
		array[i].resetSpeed();
		array[i].speedAngle = 0.0;
		array[i].putInGame();
	}

	Vector v;
	array[0].kill();
	array[0].whitePosition();
	array[8].blackPosition();

	for (Row = 0; Row < 5; Row++) {
				if(Row == 0)
				{
					v.setX(BLACK_X_START - ((BALL_RADIUS*2)*2) - 2);
					v.setZ(CENTER_Z);
					array[p1].setPosition(&v);
					p1++;
					player = p1;
				}
				else if(Row == 1)
				{
						v.setX(BLACK_X_START -(BALL_RADIUS*2) - 1);
						v.setZ(BLACK_Z_START - BALL_RADIUS);
						array[p2].setPosition(&v);
						p2++;
						
						v.setZ(BLACK_Z_START + BALL_RADIUS);
						array[p1].setPosition(&v);
						p1++;
				}
				else if(Row == 2)
				{
						v.setX(BLACK_X_START);
						v.setZ(BLACK_Z_START - (BALL_RADIUS*2));
						array[p1].setPosition(&v);
						p1++;
						
						v.setZ(BLACK_Z_START);
						array[8].setPosition(&v);//(black)
										
						v.setZ(BLACK_Z_START + (BALL_RADIUS*2));
						array[p2].setPosition(&v);
						p2++;
				}
				else if(Row == 3)
				{
					v.setX(BLACK_X_START + (BALL_RADIUS*2) + 1);
					
					v.setZ(BLACK_Z_START - (BALL_RADIUS*3) - 1);
					array[p2].setPosition(&v);
					p2++;
					
					v.setZ(BLACK_Z_START - BALL_RADIUS);
					array[p1].setPosition(&v);
					p1++;
					
					v.setZ(BLACK_Z_START + BALL_RADIUS);
					array[p2].setPosition(&v);
					p2++;
					
					v.setZ(BLACK_Z_START + (BALL_RADIUS*3) +1);
					array[p1].setPosition(&v);
					p1++;
				}
				else if(Row == 4)
				{
					v.setX(BLACK_X_START + (BALL_RADIUS*4) + 2);
					v.setZ(BLACK_Z_START - (BALL_RADIUS*4));
					array[p2].setPosition(&v);
					p2++;
					
					v.setZ(BLACK_Z_START - (BALL_RADIUS*2));
					array[p1].setPosition(&v);
					p1++;
					
					v.setZ(BLACK_Z_START);
					array[p2].setPosition(&v);
					p2++;
					
					v.setZ(BLACK_Z_START + (BALL_RADIUS*2));
					array[p1].setPosition(&v);
					p1++;
					
					v.setZ(BLACK_Z_START + (BALL_RADIUS*4));
					array[p2].setPosition(&v);
					p2++;
				}
			
		}
	}


Ball* BallArray::getBall(int number) {
	return (&array[number]);
}

Vector BallArray::getWhitePosition(void)
{
	Ball v = array[0];
	return v.getPosition();
}

Vector BallArray::getBlackPosition(void)
{
	Ball v = array[8];
	return v.getPosition();
}

int BallArray::getSize() {
	return size;
}

int BallArray::ballsLeft() {
	int i, n = 0;
	for (i = 1; i < size; i++) {
		if (array[i].inGame()) {
			n++;
		}
	}
	return n;
}
