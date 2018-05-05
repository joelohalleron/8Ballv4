#ifndef VARIABLES_H
#define VARIABLES_H

//(480x, 272y) Width and Height of LCD
//Physical properties//
#define BALL_RADIUS 5 //in pixels
#define BALL_MASS   0.5
#define RESTITUTION 0.8
#define FRICTION    0.05


#define M_PI 3.14159265358979323846

//Table Dimensions//
#define TABLE_WIDTH 			400 //in pixels 
#define TABLE_HEIGHT			250 //in pixels 
#define TABLE_COLOUR		  GREEN
#define TABLE_RAIL_COLOUR BLUE
#define TABLE_RAIL_WIDTH  15
#define HOLE_RADIUS 10
#define CENTER_X (10 + TABLE_WIDTH/2)
#define CENTER_Z (10 + TABLE_HEIGHT/2)
#define HOLE_AREA_X 10
#define HOLE_AREA_Z 10
#define X_DIMENSION ((CENTER_X + TABLE_WIDTH/2.0))
#define Z_DIMENSION ((CENTER_Z + TABLE_HEIGHT/2.0))

//Game Properties//
#define NUM_BALLS  16 //Number of balls
#define BLACK_X_START (CENTER_X + 30)
#define BLACK_Z_START (CENTER_Z)

//Joystick buttons enum
typedef enum {JLT = 0, JRT, JUP, JDN, JCR} btnId_t;

#endif

