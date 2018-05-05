#ifndef _TABLE
#define _TABLE

//						 Up
//		 ___________________________________
//		|									|
//		|									|
//		|									|
//Left	|			    Mesa				|Right
//		|									|
//		|									|
//		|									|
//		|___________________________________|
//						Down
//




#include <display.h>
#include "Vector.h"
#include "Variables.h"

class Table {

private:

	Point holes[6];

public:
	// Constructor
	Table();

  //Member functions
	void draw(Display* screen);
	Point getHoleCenter(int hole);//Get position of hole

	// Other
	bool holeArea(Point p);
	int nearestHole(Point p);
};

#endif
