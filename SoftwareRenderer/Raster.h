#ifndef _Raster_H_
#define _Raster_H_

#include "Pixel.h"
#include "Math.h"
#include "Span.h"
#include "Edge.h"
#include "Image.h"
#include "Vertex.h"

typedef unsigned char byte;

class Raster{
private:
	uint* pBuffer;
	int iWidth, iHeight;
	Pixel pixel;

public:
	Raster(int width, int height, void* buffer);
	~Raster();

	void drawTriangle(const Vertex& vertex, Image* image);
	void drawImage(int x, int y, const Image* image);

	// Buffer
	void clear();

	uint* getBuffer();
	int getBufferSize();

private:
	inline void setPixel(unsigned x, unsigned y, Pixel pixel);
	inline void setPixelEx(unsigned x, unsigned y, Pixel pixel);	// No border check
	inline Pixel getPixel(unsigned x, unsigned y);

	// Triangle
	void drawSpan(Span& span, Image* image);
	void drawEdge(Edge longEdge, Edge shortEdge, Image* image);

	bool isInRect(int2 point);

};

#endif