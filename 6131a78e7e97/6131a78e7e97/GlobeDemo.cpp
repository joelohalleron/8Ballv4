/******************************************************************************
 * Includes
 *****************************************************************************/

#include "mbed.h"

#include "LcdController.h"
#include "EaLcdBoard.h"
#include "GlobeDemo.h"

#include <math.h>

//#include "wchar.h"

/******************************************************************************
 * Typedefs and defines
 *****************************************************************************/

#define NUM_OF_DOTS 50

/******************************************************************************
 * Local variables
 *****************************************************************************/


/******************************************************************************
 * External variables
 *****************************************************************************/
extern EaLcdBoard lcdBoard;
extern bool abortTest;

/******************************************************************************
 * Local functions
 *****************************************************************************/

// Vertex structure
typedef struct
{
#ifdef USE_FLOAT
  float x, y, z;
#else
  long x, y, z;
#endif
}tVertex;

// Transformed vertices
tVertex *gRVtx;

#ifdef USE_FLOAT
// Original vertices
static tVertex *gVtx;
#else
static const tVertex gVtx[NUM_OF_DOTS] = {
{-21585, 17597, -17265},
{28493, -7790, 14183},
{13031, 27845, 11338},
{10822, 29162, -10304},
{19517, -25865, -4876},
{1283, 30949, -10687},
{-23097, 12297, 19723},
{-17162, 1188, 27888},
{-29007, -1547, 15163},
{-8182, -31729, -197},
{11599, -28575, -11073},
{25963, 12182, 15850},
{106, 10547, -31023},
{-24312, 3053, -21755},
{9966, -18803, -24916},
{17598, -6037, -26973},
{23321, 17149, -15353},
{-3265, 8867, -31376},
{-23639, 13701, 18087},
{-2433, -22123, -24049},
{21284, -11349, -22179},
{-21407, 24683, -2486},
{-32011, -4336, 5495},
{-20191, 22605, 12450},
{14752, -23540, 17376},
{-8961, -17292, -26351},
{-18078, 13561, -23727},
{10730, -23639, 19994},
{-18718, 17555, 20376},
{13626, -22837, 19144},
{-24695, -19036, -10073},
{11935, 22275, 20859},
{-2182, -28801, -15474},
{21428, -21867, -11678},
{-19601, 21558, -14991},
{24512, 10876, -18830},
{12385, 27881, 11956},
{26982, 15618, -10088},
{-16954, 19591, 20061},
{-6027, 22699, -22850},
{5453, 28825, -14598},
{-20155, -16252, -20083},
{-15962, 11757, -26089},
{-29175, -11289, -9750},
{-15370, 604, -28933},
{26009, 19868, -1575},
{24722, -17277, -12806},
{-4527, 25836, -19639},
{-22224, 10442, 21697},
{-10388, 24393, -19255}};
#endif

unsigned short GlobeDemo::isqrt(unsigned long a) const {
    unsigned long temp;
    long e;
    unsigned long x = 0;
    if((a & 0xffff0000) != 0)
        x = 444 + a / 26743;
    else if((a & 0xff00) != 0)
        x = 21 + a / 200;
    else
        x = 1 + a / 12;
    do{
        temp = a / x;
        e = (x - temp) / 2;
        x = (x + temp) / 2;
    }
    while(e != 0);
    return (unsigned short)x;
}

short GlobeDemo::_sin(short y) const {
    static short s1 = 0x6487;
    static short s3 = 0x2951;
    static short s5 = 0x4f6;
    long z, prod, sum;

    z = ((long)y * y) >> 12;
    prod = (z * s5) >> 16;
    sum = s3 - prod;
    prod = (z * sum) >> 16;
    sum = s1 - prod;

    // for better accuracy, round here
    return (short)((y * sum) >> 13);
 }

short GlobeDemo::_cos(short y) const {
    static short c0 = 0x7fff;
    static short c2 = 0x4eea;
    static short c4 = 0x0fc4;
    long z, prod, sum;
    z = ((long)y * y) >> 12;
    prod = (z * c4) >> 16;
    sum = c2 - prod;

    // for better accuracy, round here
    prod = (z * sum) >> 15;
    return (short)(c0 - prod);
}

short GlobeDemo::isine(short x) const {
    unsigned short n = (((unsigned short)x + 0x2000) >> 14) & 0x3;
    x -= n * 0x4000;
    switch(n){
        case 0:
            return _sin(x);
        case 1:
            return _cos(x);
        case 2:
            return - _sin(x);
        case 3:
            return  - _cos(x);
    }
    return 0;
 }


short GlobeDemo::icosine(short x) const {
    return isine(x + 0x4000);
 }

void GlobeDemo::initialize()
{
//  gVtx = (tVertex*)malloc(sizeof(tVertex) * NUM_OF_DOTS);
  gRVtx = (tVertex*)malloc(sizeof(tVertex) * NUM_OF_DOTS);

#ifdef USE_FLOAT
  int i;
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    gVtx[i].x = (rand() % 32768) - 16384.0f;
    gVtx[i].y = (rand() % 32768) - 16384.0f;
    gVtx[i].z = (rand() % 32768) - 16384.0f;
    float len = (float)sqrt(gVtx[i].x * gVtx[i].x + 
                            gVtx[i].y * gVtx[i].y + 
                            gVtx[i].z * gVtx[i].z);
    if (len != 0)
    {
      gVtx[i].x /= len;
      gVtx[i].y /= len;
      gVtx[i].z /= len;
    }
  }
#endif
}

#ifdef USE_FLOAT
void GlobeDemo::rotate_z(float angle)
{
  float ca = (float)cos(angle);
  float sa = (float)sin(angle);
  int i;
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    float x = gRVtx[i].x * ca - gRVtx[i].y * sa;
    float y = gRVtx[i].x * sa + gRVtx[i].y * ca;
    gRVtx[i].x = x;
    gRVtx[i].y = y;
  }
}

void GlobeDemo::rotate_y(float angle)
{
  float ca = (float)cos(angle);
  float sa = (float)sin(angle);
  int i
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    float z = gRVtx[i].z * ca - gRVtx[i].x * sa;
    float x = gRVtx[i].z * sa + gRVtx[i].x * ca;
    gRVtx[i].z = z;
    gRVtx[i].x = x;
  }
}
#else
void GlobeDemo::rotate_z(uint32_t angle)
{
  uint32_t i;
  long x,y,ca,sa;

  ca = icosine(angle);
  sa = isine(angle);
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    x = (gRVtx[i].x * ca - gRVtx[i].y * sa) / 0x7fff;
    y = (gRVtx[i].x * sa + gRVtx[i].y * ca) / 0x7fff;
    gRVtx[i].x = x;
    gRVtx[i].y = y;
  }
}

void GlobeDemo::rotate_y(uint32_t angle)
{
  uint32_t i;
  long x,z,ca,sa;

  ca = icosine(angle);
  sa = isine(angle);
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    z = (gRVtx[i].z * ca - gRVtx[i].x * sa) / 0x7fff;
    x = (gRVtx[i].z * sa + gRVtx[i].x * ca) / 0x7fff;
    gRVtx[i].z = z;
    gRVtx[i].x = x;
  }
}
#endif

#if 0
void GlobeDemo::rotate_x(float angle)
{
  float ca = (float)cos(angle);
  float sa = (float)sin(angle);
  int i;
  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    float y = gRVtx[i].y * ca - gRVtx[i].z * sa;
    float z = gRVtx[i].y * sa + gRVtx[i].z * ca;
    gRVtx[i].y = y;
    gRVtx[i].z = z;
  }
}
#endif

void GlobeDemo::render(uint32_t idx)
{
  uint32_t i;
#ifdef USE_FLOAT
  float rotz;
  float roty;
#else
  uint32_t rotz;
  uint32_t roty;
#endif

 static uint8_t cnt=0;

  if (cnt == 0)
  {
    cnt = 1;
    pFrmBuf = pFrmBuf1;
  }
  else if (cnt == 1)
  {
    cnt = 2;
    pFrmBuf = pFrmBuf2;
  }
  else
  {
    cnt = 0;
    pFrmBuf = pFrmBuf3;
  }

  graphics.setFrameBuffer(pFrmBuf);

  // rendering here
  memset((void*)(pFrmBuf), BACKGROUND_COLOR, this->windowX * this->windowY * 2);

//  lcd_fillcircle(myLcdHnd, WIDTH / 2, HEIGHT / 2, HEIGHT / 4, LARGE_CIRCLE_COLOR);
  graphics.put_circle(this->windowX / 2, this->windowY / 2, LARGE_CIRCLE_COLOR, this->windowY / 4, 1);

  memcpy(gRVtx, gVtx, sizeof(tVertex) * NUM_OF_DOTS);

#ifdef USE_FLOAT
  rotz = idx /*tick*/ * 0.0005f;
  roty = idx /*tick*/ * 0.0020f;
#else
  rotz = idx /*tick*/ * 50*5;
  roty = idx /*tick*/ * 200*5;
#endif
  rotate_y(roty);
  rotate_z(rotz);

  for (i = 0; i < NUM_OF_DOTS; i++)
  {
    uint16_t c = SMALL_CIRCLE_FRONT_COLOR;

    if (gRVtx[i].z < 0)
      c = SMALL_CIRCLE_BACK_COLOR;
#if 0
    lcd_point(myLcdHnd,
              (int)((gRVtx[i].x * (HEIGHT / 4)) / 0x7fff + WIDTH  / 2),
              (int)((gRVtx[i].y * (HEIGHT / 4)) / 0x7fff + HEIGHT / 2),
              c);
#else
//    lcd_fillcircle(myLcdHnd,
//                   (int)((gRVtx[i].x * (HEIGHT / 4)) / 0x7fff + WIDTH / 2),
//                   (int)((gRVtx[i].y * (HEIGHT / 4)) / 0x7fff + HEIGHT / 2),
//                   2,
//                   c);
    graphics.put_circle((int)((gRVtx[i].x * (this->windowY / 4)) / 0x7fff + this->windowX / 2), (int)((gRVtx[i].y * (this->windowY / 4)) / 0x7fff + this->windowY / 2), c, 2, 1);

#endif
  } 
#ifdef USE_FLOAT
  lcd_fillcircle(myLcdHnd,
                 (int)((WIDTH / 3) * cos(rotz) + WIDTH / 2),
                 (int)((WIDTH / 3) * sin(rotz) + HEIGHT / 2),
                 6,
                 SMALL_CIRCLE_FRONT_COLOR);
#else
//  lcd_fillcircle(myLcdHnd,
//                 (int)(((HEIGHT / 3) * icosine(rotz))/0x7fff + WIDTH / 2),
//                 (int)(((HEIGHT / 3) * isine(rotz))  /0x7fff + HEIGHT / 2),
//                 7,
//                 SMALL_CIRCLE_FRONT_COLOR);
    graphics.put_circle((int)(((this->windowY / 3) * icosine(rotz))/0x7fff + this->windowX / 2), (int)(((this->windowY / 3) * isine(rotz))  /0x7fff + this->windowY / 2), SMALL_CIRCLE_FRONT_COLOR, 7, 1);
#endif
}


/******************************************************************************
 * Public functions
 *****************************************************************************/
GlobeDemo::GlobeDemo(uint8_t *pFrameBuf, uint16_t dispWidth, uint16_t dispHeight) 
    : graphics((uint16_t *)pFrameBuf, dispWidth, dispHeight) {

    this->windowX = dispWidth;
    this->windowY = dispHeight;
    this->pFrmBuf  = (uint16_t *)pFrameBuf;
    this->pFrmBuf1 = (uint16_t *)pFrameBuf;
    this->pFrmBuf2 = (uint16_t *)((uint32_t)pFrameBuf + dispWidth*dispHeight*2);
    this->pFrmBuf3 = (uint16_t *)((uint32_t)pFrameBuf + dispWidth*dispHeight*4);

    initialize();
}

void GlobeDemo::run(uint32_t loops, uint32_t delayMs) {

  printf("GlobeDemo, %d loops, %dms delay\n", loops, delayMs);
  
    for(int32_t n=0;n<loops;n++) {
    
        //render globe
        render(n);
    
        //update framebuffer
        lcdBoard.setFrameBuffer((uint32_t)this->pFrmBuf);

        if (abortTest) {
            break;
        }
      
        wait_ms(delayMs);
    }
    free(gRVtx);
}

