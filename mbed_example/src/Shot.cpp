#include "Shot.h"


Shot::Shot () {
	angle = -90.0;
	strength = 0.0;
}

float Shot::getStr () {
	return (strength);
}

float Shot::getAngle () {
	return (angle);
}

void Shot::setStr (float str) {
	strength = str;
}

void Shot::setAngle (float a) {
	angle = a;
}

void Shot::addAngle (float a) {
	angle += a;

	if (angle >= 360) {
		angle = 0;
	}
	if (angle <= -360) {
		angle = 0;
	}
}

void Shot::addStr (float str) {
	if (strength + str < MAX_STR) {
		strength += str;
	}
	else {
		strength = MAX_STR;
	}
}

void Shot::subStr (float str) {
	if (strength - str > - MAX_STR) {
		strength -= str;
	}
	else {
		strength = - MAX_STR;
	}
}
