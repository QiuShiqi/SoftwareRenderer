#ifndef _Span_H_
#define _Span_H_

#include "Pixel.h"

class Span{
private:
	int iStartX, iEndX, iY;
	Pixel pixelStart, pixelEnd;

public:
	Span(int startX, int endX, int y, Pixel pixelStart, Pixel pixelEnd);

	int getStartX();
	int getEndX();
	int getY();

	Pixel getPixelStart();
	Pixel getPixelEnd();
};

#endif