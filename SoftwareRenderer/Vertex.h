#ifndef _Vertex_H_
#define _Vertex_H_

#include "Pixel.h"
#include "Math.h"

class Vertex{
public:
	float3 point;
	Pixel pixel;
	float2 uv;
public:
	Vertex(float3 point, Pixel pixel, float2 uv);

};

#endif