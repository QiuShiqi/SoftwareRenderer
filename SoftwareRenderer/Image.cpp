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
	delete this->uiBuffer;
	this->uiBuffer = nullptr;
}

Pixel Image::getPixelAt(int x, int y) const{
	return Pixel(this->uiBuffer[y * this->iWidth + x]);
}

int Image::getWidth() const{
	return this->iWidth;
}

int Image::getHeight() const{
	return this->iHeight;
}