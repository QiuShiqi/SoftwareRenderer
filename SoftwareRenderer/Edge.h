#ifndef _Edge_H_
#define _Edge_H_

#include "Pixel.h"
#include "Math.h"

class Edge{
private:
	float3 fStart;
	float2 fStartUV;

	float3 fEnd;
	float2 fEndUV;

	Pixel pixelStart, pixelEnd;

public:
	Edge(float3 start, float3 end, Pixel pixelStart, Pixel pixelEnd, float2 startUV, float2 endUV);

	float3 getStart();
	float3 getEnd();

	Pixel getPixelStart();
	Pixel getPixelEnd();

	float2 getUVStart();
	float2 getUVEnd();
};

#endif