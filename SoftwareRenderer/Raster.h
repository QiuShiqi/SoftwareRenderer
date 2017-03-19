#ifndef _Raster_H_
#define _Raster_H_

#include "Pixel.h"
#include "Math.h"

class Raster{
private:
	Pixel* pBuffer;
	int iWidth, iHeight;

public:
	Raster(int width, int height, void* buffer);
	~Raster();

	void drawPoint(int x, int y, Pixel pixel, int size);
	void drawLine(Vector2<float> start, Vector2<float> end, Pixel pixel);
	
	inline void setPixel(unsigned x, unsigned y, Pixel pixel);
	void clear();

	Pixel* getBuffer();
	int getBufferSize();
};

#endif