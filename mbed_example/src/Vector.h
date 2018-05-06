
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define Point Vector

class Vector {

private:
	float x;
	float z;

public:
	// Constructors
	Vector ();
	Vector (float x0, float z0);

	// Read properties
	Vector getVector();
	float getX ();
	float getZ ();

	// Write properties
	void setX (float x);
	void setZ (float z);
	void setVector (float x, float z);
	void setVector (Vector* v);
	void setVector (Vector v);

	// Other
	void addVector (Vector* v);
  void addVector (Vector v);
	void subVector (Vector* v);
  Vector subVector (Vector v);
	void mulVector (Vector* v);
  Vector mulVector (Vector v);
  float DotProduct (Vector v);
	
	Vector ScalarProduct(float s);
	Vector ScalarDivision(float s);
  //Normalize
  void Normalize(void);
	//Calculate terminal point of a position vector and some other unit vector
  Vector terminalPoint (Vector* v);
	// Anti-Clockwise Rotation
	void vectorRotation (float angle);
	// Calculate the angle between our Point and another Point (Related to the X axis)
	float calculateAngle (Point* p);
	// Square of the distance between our Point and another Point
	float sqrDistance (Point* p);
	
	//Operator overload
	Vector& operator+=(Vector u);
	Vector& operator-=(Vector u);
};

#endif

