#include "Vertex.h"

Vertex::Vertex(float3 point, Pixel pixel, float2 uv) {
	this->point = point;
	this->pixel = pixel;
	this->uv = uv;
}
