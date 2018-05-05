#ifndef MATRIX3X3_H
#define MATRIX3X3_H

//=================================
// forward declared dependencies
class Vector;
class Quaternion;

//=================================
// included dependencies
#include <math.h>
#include "Vector.h"
#include "Matrix3x3.h"



class Matrix3x3 {
	public:
		//elements eij: i-> row, j -> column
		float   e11, e12, e13, e21, e22, e23, e31, e32, e33;
		
		Matrix3x3(void);
		Matrix3x3(float r1c1, float r1c2, float r1c3,
							float r2c1, float r2c2, float r2c3,
							float r3c1, float r3c2, float r3c3);
		
		float det(void);
		Matrix3x3 Transpose(void);
		Matrix3x3 Inverse(void);
		
							
							
		Matrix3x3& operator+=(Matrix3x3 m);
		Matrix3x3& operator-=(Matrix3x3 m);
		Matrix3x3& operator*=(float s);
		Matrix3x3& operator/=(float s);		
							

};

/*Vector operator*(Vector u, Matrix3x3 m);
Vector operator*(Matrix3x3 m, Vector u);
Matrix3x3 MakeMatrixFromQuaternion(Quaternion q);
Matrix3x3 operator*(Matrix3x3 m1, Matrix3x3 m2);
*/







#endif
