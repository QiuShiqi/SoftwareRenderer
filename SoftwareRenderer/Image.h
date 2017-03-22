#ifndef _Image_H_
#define _Image_H_

#include "Pixel.h"

class Image{
private:
	int iWidth, iHeight;
	uint* uiBuffer;

public:
	Image(int width, int height, void* data);
	~Image();

	Pixel getPixelAt(int x, int y) const;
	Pixel getPixelUV(float u, float v);

	int getWidth() const;
	int getHeight() const;
};

#endif