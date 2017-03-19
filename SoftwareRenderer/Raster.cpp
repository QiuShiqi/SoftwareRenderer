#include "Raster.h"
#include <string.h>

Raster::Raster(int width, int height, void* buffer) : iWidth(width), iHeight(height){
	this->pBuffer = (Pixel*)buffer;
}

Raster::~Raster(){

}

void Raster::drawPoint(int x, int y, Pixel pixel, int size){
	switch(size){
	case 2:
		this->setPixel(x, y, pixel);
		this->setPixel(x+1, y, pixel);
		this->setPixel(x, y+1, pixel);
		this->setPixel(x+1, y+1, pixel);
		break;

	case 3:
		this->setPixel(x-1, y-1, pixel);
		this->setPixel(x, y-1, pixel);
		this->setPixel(x+1, y-1, pixel);
		this->setPixel(x-1, y, pixel);
		this->setPixel(x, y, pixel);
		this->setPixel(x+1, y, pixel);
		this->setPixel(x-1, y+1, pixel);
		this->setPixel(x, y+1, pixel);
		this->setPixel(x+1, y+1, pixel);
		break;

	default:
		this->setPixel(x, y, pixel);
	}

}

void Raster::drawLine(Vector2<float> start, Vector2<float> end, Pixel pixel){

}

void Raster::setPixel(unsigned x, unsigned y, Pixel pixel){

	if(x >= this->iWidth || y >= this->iHeight){
		return;
	}
	
	this->pBuffer[y * this->iWidth + x] = pixel;
}

void Raster::clear(){
	memset(this->pBuffer, 255, this->getBufferSize());
}

Pixel* Raster::getBuffer(){
	return this->pBuffer;
}

int Raster::getBufferSize(){
	return (this->iWidth * this->iHeight * sizeof(Pixel));
}