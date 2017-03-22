#ifndef _Edge_H_
#define _Edge_H_

#include "Pixel.h"
#include "Math.h"

class Edge{
private:
	int iStartX, iStartY;
	float2 fStartUV;

	int iEndX, iEndY;
	float2 fEndUV;

	Pixel pixelStart, pixelEnd;

public:
	Edge(int startX, int startY, int endX, int endY, Pixel pixelStart, Pixel pixelEnd, float2 startUV, float2 endUV);

	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();

	Pixel getPixelStart();
	Pixel getPixelEnd();

	float2 getUVStart();
	float2 getUVEnd();
};

#endif