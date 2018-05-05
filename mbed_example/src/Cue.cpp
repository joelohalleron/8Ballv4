
#include "Cue.h"

Cue::Cue() {
	angle = 0.0;
	strength = 0.0;
}


Cue::~Cue() {
}

void Cue::init() {
	
}

void Cue::draw(Display* screen, Shot* shot, Vector whitePos) {
	float angle, str;
	Vector v;
	Vector t = whitePos;
	
	angle = shot->getAngle();

	str = shot->getStr();
	str*=50;
	
	v.setX(str * sin((angle) * M_PI / 180.0));
	v.setZ(str * cos((angle) * M_PI / 180.0));
	t.terminalPoint(&v);
	setPosition(v);

	screen->drawLine(whitePos.getX(), whitePos.getZ(), t.getX(), t.getZ(), BLACK);
}

Vector Cue::rotateCue(float angle)
{
	 position.vectorRotation(angle);
}

Vector Cue::getPosition() const {
	return position;
}

void Cue::setPosition(Vector position) {
	this->position = position;
}

float Cue::getAngle() const {
	return angle;
}

void Cue::setAngle(float angle) {
	this->angle = angle;
}

void Cue::setStrength(float strength) {
	this->strength = strength;
}

float Cue::getStrength() const {
	return strength;
}
