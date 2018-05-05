
#ifndef CUE_H_
#define CUE_H_


#include <stdio.h>
#include <stdlib.h>
#include <display.h>
#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>

#include "Vector.h"
#include "Table.h"
#include "Ball.h"
#include "Shot.h"
#include "Physics.h"

#define INITIAL_DISTANCE 0.3
#define STRENGTH_FACTOR 10.0

class Cue {

private:

	Vector position;
	float angle;
	float strength;

public:
	Cue();
	virtual ~Cue();

	void init();
	void draw(Display* screen, Shot* shot, Vector whitePos);
	Vector getPosition() const;

	void setPosition(Vector position);

	float getAngle() const;

	void setAngle(float strength);

	Vector rotateCue(float angle);

	float getStrength() const;

	void setStrength(float strength);

};

#endif /* CUE_H_ */
