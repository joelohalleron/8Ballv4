/******************************************************************************
 * Includes
 *****************************************************************************/

#include "mbed.h"

#include "LcdController.h"
#include "EaLcdBoard.h"
#include "sdram.h"

#include "GlobeDemo.h"


/******************************************************************************
 * Typedefs and defines
 *****************************************************************************/

#define RESET_FLAG  \
  do { \
    if (abortTest) { \
      abortTest = false; \
      wait(0.04); \
    } \
  } while(false)

/******************************************************************************
 * Local variables
 *****************************************************************************/

static InterruptIn buttonInterrupt(P2_10);
static DigitalOut led(LED1);

/******************************************************************************
 * Global variables
 *****************************************************************************/

EaLcdBoard lcdBoard(P0_27, P0_28);
bool abortTest = false;

/******************************************************************************
 * Interrupt functions
 *****************************************************************************/

void trigger() {
    abortTest = true;
}

/******************************************************************************
 * Main
 *****************************************************************************/

int main (void) {    

    EaLcdBoard::Result result;
    LcdController::Config lcdCfg;
    uint32_t frameBuf1 = (uint32_t) SDRAM_BASE;

    printf("EA LCD Board 3D Globe Demo\n");

    // Listen for button presses
    buttonInterrupt.mode(PullUp);
    buttonInterrupt.fall(&trigger);

    do {
        // framebuffer is put in SDRAM
        if (sdram_init() == 1) {
            printf("Failed to initialize SDRAM\n");
            break;
        }
        
        result = lcdBoard.open(NULL, NULL);
        if (result != EaLcdBoard::Ok) {
            printf("Failed to open display: %d\n", result);
            break;
        }

        result = lcdBoard.setFrameBuffer(frameBuf1);
        if (result != EaLcdBoard::Ok) {
            printf("Failed to activate frameBuffer: %d\n", result);
            break;
        }

        result = lcdBoard.getLcdConfig(&lcdCfg);
        if (result != EaLcdBoard::Ok) {
            printf("Failed to get LCD configuration: %d\n", result);
            break;
        }
        
        // Prepare 3 consequtive framebuffers (2 will be used for background buffers)
        memset((void*)frameBuf1, 0x0, lcdCfg.width*lcdCfg.height*2 *3);

        GlobeDemo globeDemo((uint8_t *)frameBuf1, lcdCfg.width, lcdCfg.height);
        while (1) {
            globeDemo.run(400, 30);
            RESET_FLAG;
        }
    } while(0);

    // Blink to indicate error
    while (1) {
        led = 0;
        wait(0.2);
        led = 1;
        wait(0.2);
    }
}
