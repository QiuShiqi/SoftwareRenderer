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

void Raster::drawRectangle(int x, int y, int width, int height){
	int left = Math::getMax(x, 0);
	int top = Math::getMax(y, 0);

	int right = Math::getMin(x + width, this->iWidth);
	int bottom = Math::getMin(y + height, this->iHeight);

	for(int i = left; i < right; i++){
		for(int j = top; j < bottom; j++){
			setPixelEx(i, j, this->pixel);
		}
	}
}

void Raster::drawRectangle(int2* points, const Pixel* pixel){
	int left = Math::getMax((*(points)).getX(), 0);
	int top = Math::getMax((*(points)).getY(), 0);

	int right = Math::getMin((*(points + 2)).getX(), this->iWidth);
	int bottom = Math::getMin((*(points + 2)).getY(), this->iHeight);

	float width = right - left;
	float height = bottom - top;

	for(int i = left; i < right; i++){
		Pixel x = Pixel::Interpolation(pixel[0], pixel[1], (i - left) / width);
		Pixel y = Pixel::Interpolation(pixel[3], pixel[2], (i - left) / width);

		for(int j = top; j < bottom; j++){
			
			Pixel xy = Pixel::Interpolation(x, y, (j - top) / height);
			setPixelEx(i, j, xy);
		}
	}
}

void Raster::drawTriangle(int2 point0, int2 point1, int2 point2, Pixel pixel0, Pixel pixel1, Pixel pixel2){
	Edge edges[] = {
		Edge(point0.getX(), point0.getY(), point1.getX(), point1.getY(), pixel0, pixel1),
		Edge(point1.getX(), point1.getY(), point2.getX(), point2.getY(), pixel1, pixel2),
		Edge(point2.getX(), point2.getY(), point0.getX(), point0.getY(), pixel2, pixel0)
	};

	// Find the longest edge
	int length = edges[0].getEndY() - edges[0].getStartY();

	for(int i = 1; i < 3; i++){
		if(edges[i].getEndY() - edges[i].getStartY() > length){
			length = i;
		}
	}

	// Sort short edge
	int index = 0;
	int short1 = (index + 1) % 3;
	int short2 = (index + 2) % 3;

	// Begin draw
	this->drawEdge(edges[index], edges[short1]);
	this->drawEdge(edges[index], edges[short2]);

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
		for(int i = 0; i < count; i += 2){
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

void Raster::setPixelEx(unsigned x, unsigned y, Pixel pixel){
	this->pBuffer[y * this->iWidth + x] = pixel;
}

void Raster::drawSpan(Span& span){
	float length = span.getEndX() - span.getStartX();

	for(int x = span.getStartX(); x < span.getEndX(); x++){

		float percent = (float)(x - span.getStartX()) / length;
		Pixel pixel = Pixel::Interpolation(span.getPixelStart(), span.getPixelEnd(), percent);

		this->setPixel(x, span.getY(), pixel);
	}
}

void Raster::drawEdge(Edge longEdge, Edge shortEdge){

	float offsetLongY = longEdge.getEndY() - longEdge.getStartY();
	if(offsetLongY == 0){
		return;
	}

	float offsetShortY = shortEdge.getEndY() - shortEdge.getStartY();
	if(offsetShortY == 0){
		return;
	}

	float offsetLongX = longEdge.getEndX() - longEdge.getStartX();
	float stepLong = 1.0f / offsetLongY;
	float lengthLong = (float)(shortEdge.getStartY() - longEdge.getStartY()) / offsetLongY;

	float offsetShortX = shortEdge.getEndX() - shortEdge.getStartX();
	float stepShort = 1.0f / offsetShortY;
	float lengthShort = 0;

	for(int y = shortEdge.getStartY(); y < shortEdge.getEndY(); y++){
		int startX = longEdge.getStartX() + (int)(lengthLong * offsetLongX);
		int endX = shortEdge.getStartX() + (int)(lengthShort * offsetShortX);

		Pixel longEdgePixel = Pixel::Interpolation(longEdge.getPixelStart(), longEdge.getPixelEnd(), lengthLong);
		Pixel shoreEdgePixel = Pixel::Interpolation(shortEdge.getPixelStart(), shortEdge.getPixelEnd(), lengthShort);

		Span span(startX, endX, y, longEdgePixel, shoreEdgePixel);
		this->drawSpan(span);

		lengthLong += stepLong;
		lengthShort += stepShort;
	}
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