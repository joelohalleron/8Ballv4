#ifndef _SHOT
#define _SHOT

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STR 20

class Shot {

private:
	float strength;
	float angle;
public:
	Shot();

	float getStr ();
	float getAngle ();

	void setStr (float str);
	void setAngle (float a);
	void addAngle (float a);
	void addStr (float str);
	void subStr (float str);

};

#endif
