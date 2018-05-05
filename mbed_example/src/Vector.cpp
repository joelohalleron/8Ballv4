
#include "Vector.h"


Vector::Vector () {
	x = 0.0f;
	z = 0.0f;
}

Vector::Vector (float x0, float z0) {
	x = x0;
	z = z0;
}

float Vector::getX () {
	return x;
}

float Vector::getZ () {
	return (z);
}

void Vector::setX (float x) {
	this->x = x;
}

void Vector::setZ (float z) {
	this->z = z;
}

void Vector::setVector (float x, float z) {
	this->x = x;
	this->z = z;
}

void Vector::setVector (Vector* v) {
	x = v->getX();
	z = v->getZ();
}

void Vector::addVector (Vector* v) {
	x += v->x;
	z += v->z;
}

void Vector::subVector (Vector* v) {
	x -= v->x;
	z -= v->z;
}

void Vector::mulVector (Vector* v) {
	x *= v->x;
	z *= v->z;
}

void Vector::vectorRotation (float angle) {
	float oldX;
	oldX = x;
	x = sin(angle) * z + cos(angle) * x;
	z = cos(angle) * z - sin(angle) * oldX;
}

Vector Vector::terminalPoint (Vector* v)
{
	Vector tp(x += v->getX(), z+=v->getZ() );
	return tp;
}

float Point::calculateAngle (Point* p) {
	float angle;

	Point aux1(x, z);
	aux1.subVector(p);

	angle = atan2(aux1.getZ(), aux1.getX());
	return angle;
}

float Point::sqrDistance (Point* p) {
	return ( (x - p->x) * (x - p->x) + (z - p->z) * (z - p->z) );
}
