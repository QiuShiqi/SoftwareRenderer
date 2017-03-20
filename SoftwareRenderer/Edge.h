#ifndef _Edge_H_
#define _Edge_H_

#include "Pixel.h"

class Edge{
private:
	int iStartX, iStartY;
	int iEndX, iEndY;
	Pixel pixelStart, pixelEnd;

public:
	Edge(int startX, int startY, int endX, int endY, Pixel pixelStart, Pixel pixelEnd);

	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();

	Pixel getPixelStart();
	Pixel getPixelEnd();
};

#endif