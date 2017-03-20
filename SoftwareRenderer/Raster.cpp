#include "Raster.h"
#include <string.h>

Raster::Raster(int width, int height, void* buffer) : iWidth(width), iHeight(height), pixel(){
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

void Raster::drawLine(float2 start, float2 end, Pixel startPixel, Pixel endPixel){
	float offsetX = start.getX() - end.getX();
	float offsetY = start.getY() - end.getY();	

	if(offsetX == 0 && offsetY == 0){	// 距离只有一个点
		setPixel(start.getX(), start.getY(), startPixel);
	}

	if(Math::getAbs(offsetX) > Math::getAbs(offsetY)){
		float maxX = Math::getMax(start.getX(), end.getX());
		float minX = Math::getMin(start.getX(), end.getX());

		float slope = offsetY / offsetX;	// 斜率
		float length = maxX - minX;	// 计算长度

		for(float x = minX; x <= maxX; x += 1.0f){
			float y = start.getY() + (x - start.getX()) * slope;

			//颜色插值计算
			float percent = (x - minX) / length;
			Pixel pixel = Pixel::Interpolation(startPixel, endPixel, percent);

			this->setPixel(x, y, pixel);
		}

	}else{
		float maxY = Math::getMax(start.getY(), end.getY());
		float minY = Math::getMin(start.getY(), end.getY());

		float slope = offsetX / offsetY;	// 斜率
		float length = maxY - minY;	// 计算长度

		for(float y = minY; y <= maxY; y += 1.0f){
			float x = start.getX() + (y - start.getY()) * slope;

			//颜色插值计算
			float percent = (y - minY) / length;
			Pixel pixel = Pixel::Interpolation(startPixel, endPixel, percent);

			this->setPixel(x, y, pixel);
		}
	}

}

void Raster::drawArrays(DRAWMODE mode, const float2* points, int count){

	switch(mode){
	case DM_POINTS:
		for(int i = 0; i < count; i++){
			this->drawPoints(points[i], this->pixel);	// 颜色默认值
		}

		break;

	case DM_LINES:
		count = count / 2 * 2;
		for(int i = 0; i < count; i++){
			this->drawLine(points[i], points[i + 1], this->pixel, this->pixel);
		}

		break;

	case DM_LINE_LOOP:
		this->drawLine(points[0], points[1], this->pixel, this->pixel);

		for(int i = 2; i < count; i++){
			this->drawLine(points[i - 1], points[i], this->pixel, this->pixel);
		}

		this->drawLine(points[0], points[count - 1], this->pixel, this->pixel);
		break;

	case DM_LINE_STRIP:
		this->drawLine(points[0], points[1], this->pixel, this->pixel);

		for(int i = 2; i < count; i++){
			this->drawLine(points[i - 1], points[i], this->pixel, this->pixel);
		}

		break;
	}
}

void Raster::drawPoints(float2 dot, Pixel pixel){

}

void Raster::setPixel(unsigned x, unsigned y, Pixel pixel){

	if(x >= this->iWidth || y >= this->iHeight){
		return;
	}

	this->pBuffer[y * this->iWidth + x] = pixel;
}

void Raster::clear(){
	memset(this->pBuffer, 0, this->getBufferSize());
}

Pixel* Raster::getBuffer(){
	return this->pBuffer;
}

int Raster::getBufferSize(){
	return (this->iWidth * this->iHeight * sizeof(Pixel));
}