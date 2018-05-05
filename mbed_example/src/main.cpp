#include <mbed.h>
#include <MMA7455.h>
#include <LM75B.h>
#include <display.h>
#include "Game.h"
#include "Variables.h"
#include "Vector.h"
#include "Matrix3x3.h"
#include "Physics.h"
#include "Interface.h"
#include "Ball.h"
#include "bitmap.h"



#define TABLE_COLOUR GREEN
#define RAIL_COLOUR RED



//Declare ethernet link
Ethernet Eth;

//This is how you call a static method of class Display
//Returns a pointer to an object that manages the display screen 
Display *screen = Display::theDisplay();

/* Setup Double-buffering:
    The LCD display object uses malloc internally, to get enougth memory for
    3 frame buffers.  The display object renders into the buffer supplied
    through setFb, it is returned through getFb.
    The LPC4088 has an LCD driver that displays the contents of the buffer
    supplied through the UPBASE register.
    This function generates a pointer to the second buffer, and sets the
    display to use one, and the driver to use the other.
*/
void init_double_buffering(void)
{
    uint16_t *buffer = screen->getFb();
    uint16_t *frame2 = buffer+(480*272);
    LPC_LCD->UPBASE = (uint32_t)frame2;
}

/* swap the frame buffers used by the Display GFX library
    and the LCD driver
*/
void swap_double_buffers(void)
{
    unsigned int b;
    b = LPC_LCD->UPBASE;
    LPC_LCD->UPBASE = (uint32_t)screen->getFb();
    screen->setFb((uint16_t *)b);
}


//Interface interface = Interface(screen);

//Declare Game
Game game = Game(screen);

//Declare draw methods
void drawTable(uint16_t colour);
void drawBalls(Ball ba[]);

//Declare output object for LED1
DigitalOut led1(LED1);

 //Initialise Joystick   
static DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);
bool jsPrsdAndHeld(btnId_t b);

//Input object for the potentiometer
AnalogIn pot(p15);
float potVal = 0.0;
  
//Object to manage the accelerometer
MMA7455 acc(P0_27, P0_28);
bool accInit(MMA7455& acc); //prototype of init routine
int32_t accVal[3];

//Object to manage temperature sensor
LM75B lm75b(P0_27, P0_28, LM75B::ADDRESS_1);
float tempVal = 0.0;




/*Timer interrupt and handler
void timerHandler(); //prototype of handler function
int tickCt = 0;*/


int main() {

  char myword[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	char data[8];
	lm75b.open();
  init_double_buffering();
	//Establish ethernet link
	Eth.link();	
	//Draw the table
	//Initialise display
	
  while (true) {

		
      potVal = pot.read();//To be used for shot power
	    screen->fillScreen(WHITE);
      screen->setTextColor(BLACK, WHITE);

		
		
		
			 if(jsPrsdAndRlsd(JUP)) { 
				game.processKey(JUP);
			} else if (jsPrsdAndRlsd(JDN)) {
				game.processKey(JDN);
			} else if (jsPrsdAndRlsd(JLT)) { // NB response to JS L, R reversed
				game.processKey(JLT);                 //   because JS is upside-down
			} else if (jsPrsdAndRlsd(JRT)) {
				game.processKey(JRT);
			} else if (jsPrsdAndRlsd(JCR)) {
				game.processKey(JCR);
			}
			
			/*game.setStrength(potVal);
			game.draw();//display
			game.loop();//game loop*/
			if (Eth.link()) {
               screen->setCursor(330,0);
							 screen->printf("Online");
      } else {
                screen->setCursor(330,0);
								screen->printf("Offline");
      }
			
			//WriteCode//Eth.write(myword, sizeof(myword));
			//WriteCode//Eth.send();
			/*ReadCode*/ 
			Eth.read(data, Eth.receive());
			screen->setCursor(200,100);
			screen->printf(data);
			swap_double_buffers();
			
    wait(0.01); //5 milliseconds
  }
}

bool accInit(MMA7455& acc) {
  bool result = true;
  if (!acc.setMode(MMA7455::ModeMeasurement)) {
    // screen->printf("Unable to set mode for MMA7455!\n");
    result = false;
  }
  if (!acc.calibrate()) {
    // screen->printf("Failed to calibrate MMA7455!\n");
    result = false;
  }
  // screen->printf("MMA7455 initialised\n");
  return result;
}

/*Definition of timer interrupt handler
void timerHandler() {
  tickCt++;
  led1 = !led1; //every tick, toggle led1
}*/

/* Definition of Joystick press capture function
 * b is one of JLEFT, JRIGHT, JUP, JDOWN - from enum, 0, 1, 2, 3
 * Returns true if this Joystick pressed then released, false otherwise.
 *
 * If the value of the button's pin is 0 then the button is being pressed,
 * just remember this in savedState.
 * If the value of the button's pin is 1 then the button is released, so
 * if the savedState of the button is 0, then the result is true, otherwise
 * the result is false. */
	bool jsPrsdAndRlsd(btnId_t b) {
	bool result = false;
	uint32_t state;
	static uint32_t savedState[4] = {1,1,1,1};
  //initially all 1s: nothing pressed
	state = jsBtns[b].read();
  if ((savedState[b] == 0) && (state == 1)) {
		result = true;
	}
	savedState[b] = state;
	return result;
}
	


