#ifndef _Vertex_H_
#define _Vertex_H_

#include "Pixel.h"
#include "Math.h"

class Vertex{
public:
	int2 point0, point1, point2;
	Pixel pixel0, pixel1, pixel2;
	float2 uv0, uv1, uv2;
public:
	Vertex(int2 point0, int2 point1, int2 point2, Pixel pixel0, Pixel pixel1, Pixel pixel2, float2 uv0, float2 uv1, float2 uv2);

};

#endif