#include "Image.h"
#include<string.h> 

Image::Image(int width, int height, void* data){
	if(width == 0 || height == 0 || data == nullptr){
		this->iWidth = 0;
		this->iHeight = 0;
		this->uiBuffer = 0;

	}else{
		this->iWidth = width;
		this->iHeight = height;
		this->uiBuffer = new uint[width * height];
		memcpy(this->uiBuffer, data, width * height * sizeof(uint));
	}
}

Image::~Image(){
	delete []this->uiBuffer;
	this->uiBuffer = nullptr;
}

Pixel Image::getPixelAt(int x, int y) const{
	return Pixel(this->uiBuffer[y * this->iWidth + x]);
}

Pixel Image::getPixelUV(float u, float v){
	float x = u * this->iWidth;
	float y = v * this->iHeight;

	return this->getPixelAt((unsigned)(x) % this->iWidth, (unsigned)(y) % this->iHeight);
}

int Image::getWidth() const{
	return this->iWidth;
}

int Image::getHeight() const{
	return this->iHeight;
}
