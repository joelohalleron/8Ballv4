
#ifndef _PHYSICS
#define _PHYSICS

//Position correction at collision time
#define FACTOR 0.5
//was 0.0001

#include "Vector.h"
#include "Ball.h"
#include "Table.h"
#include "Shot.h"


class Physics {

private:
	enum enumTable { NONE = 0, LEFT, RIGHT, UP, DOWN };
	int tableRegion;

	enum enumType { RAY = 1, CORNER };
	int type;

	int rayIndex;
	int* collisionOrder;
	int totalCollisions;
	
	Vector vForces; //Total resultant force for an object
	Vector vImpactForces; //The resolution forces of an impact
	Vector vCollisionNormal; //The collision normal for a collision
	Vector vRelativeVelocity; //Relative velocity of two objects
	

public:
	int firstCollision;

private:
	void Friction (Ball* b);
	void energyLoss (Ball* b);
	int insertDistance (float* distArray, int size, float dist);
	void insertIndex (int* indexArray, int size, int value, int position);

	bool checkBallCollision (Ball* a, Ball* b, float* pDist);
	void checkTableCollision (Table* t, Ball* b);
	bool checkHoleCollision (Table* t, Ball* b, int hole);

	void fixBallCollision (Ball* a, Ball* b);
	void fixTableCollision (Ball* b);

public:
	Physics();
	~Physics();

	void getCollisionOrder (BallArray* ba, int ballIndex);
	bool hasCollisions();
	int getCollision();

	void movement (Ball* b);

	void ballCollision (Ball* a, Ball* b);
	bool tableCollision (Table* t, Ball* b);
	bool holeAreaCollision (Table* t, Ball* b);
	void respawnCollision (Table* t, BallArray* ba, bool upward);

	void hitCueBall (Ball* cueBall, Shot* shot);
};

#endif
