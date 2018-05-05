
#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
public:

	Graphics(uint16_t *pFrmBuf, uint16_t dispWidth, uint16_t dispHeight);

	void setFrameBuffer( uint16_t *pFrmBuf );
	void put_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int16_t color);
    void put_circle( int32_t cx, int32_t cy, int16_t color, int32_t radius, int32_t Filled );

protected:
	uint16_t windowX;
	uint16_t windowY;
	uint16_t *pFrmBuf;
	
    int32_t abs(int32_t v1) const;
    
    virtual void plot4points( int32_t cx, int32_t cy, int32_t x, int32_t y, int16_t color, int32_t Filled );
    void plot8points( int32_t cx, int32_t cy, int32_t x, int32_t y, int16_t color, int32_t Filled );
    
};

#endif


