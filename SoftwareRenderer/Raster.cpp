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
	float offsetX = start.getX() - end.getX();
	float offsetY = start.getY() - end.getY();	

	if(offsetX == 0 && offsetY == 0){	// 距离只有一个点
		setPixel(start.getX(), start.getY(), pixel);
		return;
	}

	if(offsetX == 0){
		float maxY = Base::getMax(start.getY(), end.getY());
		float minY = Base::getMin(start.getY(), end.getY());

		for(float y = minY; y <= maxY; y += 1.0f){
			this->setPixel(start.getX(), y, pixel);
		}

	}else if(offsetY == 0){
		float maxX = Base::getMax(start.getX(), end.getX());
		float minX = Base::getMin(start.getX(), end.getX());

		for(float x = minX; x <= maxX; x += 1.0f){
			this->setPixel(x, start.getY(), pixel);
		}

	}else{

		if(Base::getAbs(offsetX) > Base::getAbs(offsetY)){
			float maxX = Base::getMax(start.getX(), end.getX());
			float minX = Base::getMin(start.getX(), end.getX());

			float slope = offsetY / offsetX;	// 斜率

			for(float x = minX; x <= maxX; x += 1.0f){
				float y = start.getY() + (x - start.getX()) * slope;
				this->setPixel(x, y, pixel);
			}

		}else{
			float maxY = Base::getMax(start.getY(), end.getY());
			float minY = Base::getMin(start.getY(), end.getY());

			float slope = offsetX / offsetY;	// 斜率

			for(float y = minY; y <= maxY; y += 1.0f){
				float x = start.getX() + (y - start.getY()) * slope;
				this->setPixel(x, y, pixel);
			}
		}


	}

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