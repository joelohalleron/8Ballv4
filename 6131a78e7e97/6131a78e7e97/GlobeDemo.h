
#ifndef GLOBEDEMO_H
#define GLOBEDEMO_H

#include "Graphics.h"
#include "GFXFb.h"

class GlobeDemo {
public:

    /** Set the address of the frame buffer to use.
     *
     *  It is the content of the frame buffer that is shown on the
     *  display. All the drawing on the frame buffer can be done
     *  'offline' and whenever it should be shown this function
     *  can be called with the address of the offline frame buffer.
     *
     *  @param pFrameBuf  Pointer to the frame buffer, which must be
     *                    3 times as big as the frame size (for tripple
     *                    buffering).
     *         dispWidth  The width of the display (in pixels).
     *         dispHeight The height of the display (in pixels).
     *         loops      Number of loops in the demo code.
     *         delayMs    Delay in milliseconds between schreen updates.
     *
     *  @returns
     *       none
     */
    GlobeDemo(uint8_t *pFrameBuf, uint16_t dispWidth, uint16_t dispHeight);
    
    void run(uint32_t loops, uint32_t delayMs);

private:
    enum Constants {
        BACKGROUND_COLOR         = BLACK,
        LARGE_CIRCLE_COLOR       = 0x39e7, //DARK_GRAY
        SMALL_CIRCLE_FRONT_COLOR = WHITE,
        SMALL_CIRCLE_BACK_COLOR  = 0x7bef, //LIGHT_GRAY
    };

    int32_t windowX;
    int32_t windowY;
    uint16_t *pFrmBuf;
    uint16_t *pFrmBuf1;
    uint16_t *pFrmBuf2;
    uint16_t *pFrmBuf3;
    
    Graphics graphics;
    
    unsigned short isqrt(unsigned long a) const;
    short _sin(short y) const;
    short _cos(short y) const;
    short isine(short x) const;
    short icosine(short x) const;
    void rotate_z(uint32_t angle);
    void rotate_y(uint32_t angle);
    void initialize();
    void render(uint32_t idx);

};

#endif /* GLOBEDEMO_H */

