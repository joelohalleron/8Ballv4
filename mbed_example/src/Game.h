#ifndef _GAME
#define _GAME

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>

#include "Physics.h"
#include "Interface.h"

#include "Variables.h"
#include "Shot.h"
#include "Table.h"
#include "Ball.h"
#include "ExpandedTimer.h"



enum MODE {
	DIRECTION, SHOT, PHYSICS, FIM
};


struct Player {
    int p_id;
    bool final;
    int total_balls;
    int previous_total_balls;

    Player();
    Player(int id, int total);
};






class Game {

private:
    
    Player P1;
    Player P2;
    bool cueBall_collided;
    int ball_hit;
    //FIM DAS NOSSAS
		int currentPlayer;
		Shot shot;
		
	Display* screen;
	Table table;
	BallArray ba;
	Ball* cueBall;
	Ball* blackBall;

	Interface interface;
	Physics physics;

	MODE mode;
	ExpandedTimer physicsTimer;
	ExpandedTimer animationTimer;


	float strLevel;
	float strength;
	void setDirection(btnId_t b);

	void updateShot();
	void applyPhysics();
	bool checkCueBall();
	void executeShot();

	
	void drawShot();
	void drawSelection();
	bool turnEnded();
	void processEnd();
	bool illegalMove(int pl);
	void killPlayerBall(int pl);
	void updateBallCount();
	void processEndGame(int pl);
	bool isOver();

	void respawnCueBall();
	void physicsInterface();
	int op_id(int pl);

public:

	//Public
	Game();
  Game(Display* screen);
  void initializeGame();
	void SetDisplay(Display *screen);
	void processKey(btnId_t b);
	void loop();
	void draw();
	void setStrength(float s);

};



#endif
