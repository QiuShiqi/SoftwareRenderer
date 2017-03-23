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
	matrix3 matrix;

public:
	Raster(int width, int height, void* buffer);
	~Raster();

	void drawTriangle(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2, Image* image);
	void drawImage(int x, int y, const Image* image);

	void setMatrix(const matrix3& matrix);

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

};

#endif