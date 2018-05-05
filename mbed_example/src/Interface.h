#ifndef _INTERFACE
#define _INTERFACE


#include <stdio.h>
#include <stdlib.h>
#include <display.h>
#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>


#include "Cue.h"
#include "Vector.h"
#include "Table.h"
#include "Ball.h"
#include "Shot.h"
#include "Physics.h"



class Interface {

private:
	Table* table;
	Cue cue;
	Ball* cueBall;
	Ball* blackBall;
	BallArray* ba;
	Display* screen;


public:
	Interface();
	~Interface();
	Interface(Display *screen);
	void init();
	void drawTable();
	void drawBalls();
	void drawCue(Shot *shot, bool guideLine);
	void drawShotStrength(float s);
	void drawIllegalMove(int player);
  void playerTurn(int pID);
	void playerWon(int pID);

	Table *getTable() const;
	void setTable(Table *table);
	Ball *getCueBall() const;
	void setCueBall(Ball *cueBall);
	Ball *getBlackBall() const;
	void setBlackBall(Ball *blackBall);
	BallArray *getBallsArray() const;
	void setBallsArray(BallArray *ba);
	void SetDisplay(Display *screen);
};



#endif

