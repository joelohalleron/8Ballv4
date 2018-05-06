
#include "Vector.h"


Vector::Vector () {
	x = 0.0f;
	z = 0.0f;
}

Vector::Vector (float x0, float z0) {
	x = x0;
	z = z0;
}

//+= Operator for vector addition
Vector& Vector::operator+=(Vector u)
{
	x += u.x;
	z += u.z;
	return *this;
}

//-= Operator for Vector subtraction 
Vector& Vector::operator-=(Vector u)
{
	x -= u.x;
	z -= u.z;
	return *this;
}

Vector Vector::getVector()
{
	return Vector(x,z);
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

void Vector::setVector (Vector v) {
	x = v.getX();
	z = v.getZ();
}

void Vector::addVector (Vector* v) {
	x += v->x;
	z += v->z;
}

void Vector::addVector (Vector v) {
	x += v.x;
	z += v.z;
}

void Vector::subVector (Vector* v) {
	x -= v->x;
	z -= v->z;
}

Vector Vector::subVector (Vector v) {
	Vector a;
	a.setX(x - v.x);
	a.setZ(z - v.z);
	return a;
}


//Normalise
void Vector::Normalize(void)
{
	float const tol = 0.0001f;
	float m = (float) sqrt(x*x + z*z);
	if(m<=tol) m=1;
	x /= m;
	z /= m;
	
	if(fabs(x) < tol) x = 0.0f;
	if(fabs(z) < tol) z = 0.0f;	
}

void Vector::mulVector (Vector* v) {
	x *= v->x;
	z *= v->z;
}

Vector Vector::mulVector (Vector v) {
	Vector a;
	a.x = x * v.x;
	a.z = z * v.z;
	
	return a;
}
float Vector::DotProduct(Vector v){
	Vector a;
	return (a.x * v.x + a.z*v.z);
}

Vector Vector::ScalarProduct(float s){
	Vector a;
	a.x = x*s;
	a.z = z*s;
	return a;
}

Vector Vector::ScalarDivision(float s)
{
  
	return Vector(x/s, z/s);

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
