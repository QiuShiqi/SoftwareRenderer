#ifndef _Raster_H_
#define _Raster_H_

#include "Pixel.h"
#include "Math.h"
#include "Span.h"
#include "Edge.h"

class Raster{
public:
	enum DRAWMODE{
		DM_POINTS = 0,
		DM_LINES = 1,
		DM_LINE_LOOP = 2,
		DM_LINE_STRIP = 3
	};

private:
	Pixel* pBuffer;
	int iWidth, iHeight;
	Pixel pixel;

public:
	Raster(int width, int height, void* buffer);
	~Raster();

	void drawPoint(int x, int y, Pixel pixel, int size);
	void drawRectangle(int x, int y, int width, int height);
	void drawRectangle(int2* points, const Pixel* pixel);
	void drawTriangle(int2 point0, int2 point1, int2 point2, Pixel pixel0, Pixel pixel1, Pixel pixel2);

	void drawArrays(DRAWMODE mode, const float2* points, int count);

	void clear();

	Pixel* getBuffer();
	int getBufferSize();

private:
	inline void setPixel(unsigned x, unsigned y, Pixel pixel);
	inline void setPixelEx(unsigned x, unsigned y, Pixel pixel);	// No border check

	void drawLine(float2 start, float2 end, Pixel startPixel, Pixel endPixel);
	void drawPoints(float2 dot, Pixel pixel);

	// Triangle
	void drawSpan(Span& span);
	void drawEdge(Edge longEdge, Edge shortEdge);
};

#endif