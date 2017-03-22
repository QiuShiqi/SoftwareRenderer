#ifndef _Span_H_
#define _Span_H_

#include "Pixel.h"
#include "Math.h"

class Span{
private:
	int iStartX, iEndX, iY;
	Pixel pixelStart, pixelEnd;
	float2 fStartUV, fEndUV;

public:
	Span(int startX, int endX, int y, Pixel pixelStart, Pixel pixelEnd, float2 startUV, float2 endUV);

	int getStartX();
	int getEndX();
	int getY();

	Pixel getPixelStart();
	Pixel getPixelEnd();

	float2 getStartUV();
	float2 getEndUV();
};

#endif