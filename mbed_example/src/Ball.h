#ifndef _BALL
#define _BALL


#define SPEED_FACTOR 150000
#define ROTATION_FACTOR 1000

#include <mbed.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <display.h>
#include "Variables.h"
#include "Vector.h"

struct Ball_Properties {
	Vector center;
};

class Ball {

	friend class BallArray;

private:

	bool gameStatus;
	int number;

	Vector center;

	Vector speed;
	float speedAngle;

public:

	void draw(Display* screen, uint16_t colour);

	// Read Properties
	bool inGame();
	int getNumber();
	Vector getPosition();
	float getXPosition();
	float getZPosition();
	Vector getSpeed();
	float getXSpeed();
	float getYSpeed();
	float getLastAngle();

	// Write Properties
	void setPosition(Vector* v);
	void setXPosition(float x);
	void setYPosition(float y);
	void setSpeed(Vector* v);

	// Position Functions
	void addPosition(Vector* v);
	void addXPosition(float value);
	void addYPosition(float value);
	void subPosition(Vector* v);
	void subXPosition(float value);
	void subYPosition(float value);

	// Speed functions
	bool isMoving();
	float calculateSpeedAngle();
	void resetSpeed();
	void addSpeed(Vector* v);
	void subSpeed(Vector* v);
	void rotateSpeed(float angle);
	void tradeXSpeed(Ball* b);
	void tradeYSpeed(Ball* b);
	void reverseXSpeed();
	void reverseZSpeed();

	// Other
	void putInGame();
	void kill();
	void whitePosition();
	void blackPosition();
};

class BallArray {

private:
	Ball array[NUM_BALLS];
	int size;

public:
	// Array Functions
	void initializeBallArray(int totalBalls);
	Ball* getBall(int number);
	int getSize();
	int ballsLeft();
	Vector getWhitePosition(void);//Returns position of the white
	Vector getBlackPosition(void);
};

#endif
