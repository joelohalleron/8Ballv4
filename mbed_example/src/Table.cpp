#include "Table.h"


// Constructor
Table::Table() {
	holes[0].setVector(15, 15);
	holes[1].setVector(CENTER_X, 15);
	holes[2].setVector(X_DIMENSION, 15);
	holes[3].setVector(15, Z_DIMENSION);
	holes[4].setVector(CENTER_X, Z_DIMENSION);
	holes[5].setVector(X_DIMENSION, Z_DIMENSION);
}



void Table::draw(Display* screen) {
	
	screen->fillRect(10, 10, TABLE_WIDTH, TABLE_HEIGHT, TABLE_COLOUR);
	screen->fillCircle(holes[0].getX(),holes[0].getZ(), HOLE_RADIUS, BLACK);
  screen->fillCircle(holes[1].getX(),holes[1].getZ(), HOLE_RADIUS, BLACK);
	screen->fillCircle(holes[2].getX(),holes[2].getZ(), HOLE_RADIUS, BLACK);
	screen->fillCircle(holes[3].getX(),holes[3].getZ(), HOLE_RADIUS, BLACK);
	screen->fillCircle(holes[4].getX(),holes[4].getZ(), HOLE_RADIUS, BLACK);
	screen->fillCircle(holes[5].getX(),holes[5].getZ(), HOLE_RADIUS, BLACK);

}

Point Table::getHoleCenter(int hole) {
	return (holes[hole]);
}

// Other
bool Table::holeArea(Point p) {
	float x = p.getX();
	float z = p.getZ();

	if ((z < Z_DIMENSION - HOLE_AREA_Z) && (z > (Z_DIMENSION - (TABLE_HEIGHT/2)  + HOLE_AREA_Z))) {

		return false;
	}
		if ((x > (X_DIMENSION - (TABLE_WIDTH/2))  + HOLE_AREA_X) && (x < X_DIMENSION - HOLE_AREA_X)) {
			return false;
		}
		/*if ((x < X_DIMENSION - HOLE_AREA_X) && (x > HOLE_AREA_X)) {
			return false;
		}*/
		return true;
	}

	

//Nearest hole given point p
int Table::nearestHole(Point p) {
	float x, z;
	x = p.getX();
	z = p.getZ();

	if ((x <= 10 * HOLE_AREA_X) && (x >= -10 * HOLE_AREA_X)) {
		if (z > 0.0)
			return 1;
		else
			return 4;
	}
	if (x < HOLE_AREA_X) {
		if (z > 0.0)
			return 0;
		else
			return 5;
	}
	if (x > HOLE_AREA_X) {
		if (z > 0.0)
			return 2;
	}
	return 3;
}




