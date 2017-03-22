#include "Vertex.h"

Vertex::Vertex(int2 point0, int2 point1, int2 point2, Pixel pixel0, Pixel pixel1, Pixel pixel2, float2 uv0, float2 uv1, float2 uv2) {
	this->point0 = point0;
	this->point1 = point1;
	this->point2 = point2;

	this->pixel0 = pixel0;
	this->pixel1 = pixel1;
	this->pixel2 = pixel2;

	this->uv0 = uv0;
	this->uv1 = uv1;
	this->uv2 = uv2;
}

