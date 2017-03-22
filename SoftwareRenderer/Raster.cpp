#include "Raster.h"
#include <string.h>
#include <stdlib.h>

Raster::Raster(int width, int height, void* buffer) : iWidth(width), iHeight(height), pixel() {
	this->pBuffer = (uint*)buffer;
}

Raster::~Raster(){

}

void Raster::drawTriangle(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2, Image* image){

	if(!(this->isInRect(vertex0.point)) && !(this->isInRect(vertex1.point)) && !(this->isInRect(vertex2.point))){
		return;
	}

	Edge edges[3] = {
		Edge(vertex0.point.getX(), vertex0.point.getY(), vertex1.point.getX(), vertex1.point.getY(), vertex0.pixel, vertex1.pixel, vertex0.uv, vertex1.uv),
		Edge(vertex1.point.getX(), vertex1.point.getY(), vertex2.point.getX(), vertex2.point.getY(), vertex1.pixel, vertex2.pixel, vertex1.uv, vertex2.uv),
		Edge(vertex2.point.getX(), vertex2.point.getY(), vertex0.point.getX(), vertex0.point.getY(), vertex2.pixel, vertex0.pixel, vertex2.uv, vertex0.uv)
	};

	// Find the longest edge
	int length = edges[0].getEndY() - edges[0].getStartY();
	int index = 0;

	for(int i = 1; i < 3; i++){
		int max = edges[i].getEndY() - edges[i].getStartY();

		if(max > length){
			length = max;
			index = i;
		}
	}

	// Sort short edge
	int short1 = (index + 1) % 3;
	int short2 = (index + 2) % 3;

	// Begin draw
	this->drawEdge(edges[index], edges[short1], image);
	this->drawEdge(edges[index], edges[short2], image);

}

void Raster::drawImage(int x, int y, const Image* image){

	int left = Math::getMax(x, 0);
	int top = Math::getMax(y, 0);

	int right = Math::getMin(x + image->getWidth(), this->iWidth);
	int bottom = Math::getMin(y + image->getHeight(), this->iHeight);

	for(int i = left; i < right; i++){
		for(int j = top; j < bottom; j++){
			Pixel pixel = image->getPixelAt(i - left, j - top);
			setPixelEx(i, j, pixel);
		}
	}

}

void Raster::drawArrays(DRAWMODE type, int start, int count){

}

void Raster::setPixel(unsigned x, unsigned y, Pixel pixel){

	if(x >= this->iWidth || y >= this->iHeight){
		return;
	}

	this->pBuffer[y * this->iWidth + x] = pixel.getColor();
}

void Raster::setPixelEx(unsigned x, unsigned y, Pixel pixel){
	this->pBuffer[y * this->iWidth + x] = pixel.getColor();
}

Pixel Raster::getPixel(unsigned x, unsigned y){
	return Pixel(this->pBuffer[y * this->iWidth + x]);
}

void Raster::drawSpan(Span& span, Image* image){

	float length = span.getEndX() - span.getStartX();
	float step = 1.0f / length;
	float percent = 0;

	// Vertical crop image
	int startX = Math::getMax(span.getStartX(), 0);
	int endX = Math::getMin(span.getEndX(), this->iWidth);
	percent += (startX - span.getStartX()) / length;

	for(int x = startX; x < endX; x++){

		//Pixel pixelColor = Pixel::Interpolation(span.getPixelStart(), span.getPixelEnd(), percent);

		float2 uv = Pixel::Interpolation(span.getStartUV(), span.getEndUV(), percent);
		Pixel pixelUV = image->getPixelUV(uv.getX(), uv.getY());

		//Pixel pixel = pixelColor + pixelUV;
		this->setPixel(x, span.getY(), pixelUV);

		percent += step;
	}

}

void Raster::drawEdge(Edge longEdge, Edge shortEdge, Image* image){

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

	// Horizontal crop image
	int longStartY = Math::getMax(longEdge.getStartY(), 0);
	int longEndY = Math::getMin(longEdge.getEndY(), this->iHeight);
	lengthLong += (longStartY - longEdge.getStartY()) / offsetLongY;

	float offsetShortX = shortEdge.getEndX() - shortEdge.getStartX();
	float stepShort = 1.0f / offsetShortY;
	float lengthShort = 0;

	// Horizontal crop image
	int shortStartY = Math::getMax(shortEdge.getStartY(), 0);
	int shortEndY = Math::getMin(shortEdge.getEndY(), this->iHeight);
	lengthShort += (shortStartY - shortEdge.getStartY()) / offsetShortY;

	for(int y = shortStartY; y < shortEndY; y++){
		int startX = longEdge.getStartX() + (int)(lengthLong * offsetLongX);
		int endX = shortEdge.getStartX() + (int)(lengthShort * offsetShortX);

		Pixel longEdgePixel = Pixel::Interpolation(longEdge.getPixelStart(), longEdge.getPixelEnd(), lengthLong);
		Pixel shoreEdgePixel = Pixel::Interpolation(shortEdge.getPixelStart(), shortEdge.getPixelEnd(), lengthShort);

		float2 startUV = Pixel::Interpolation(longEdge.getUVStart(), longEdge.getUVEnd(), lengthLong);
		float2 endUV = Pixel::Interpolation(shortEdge.getUVStart(), shortEdge.getUVEnd(), lengthShort);

		Span span(startX, endX, y, longEdgePixel, shoreEdgePixel, startUV, endUV);
		this->drawSpan(span, image);

		lengthLong += stepLong;
		lengthShort += stepShort;
	}

}

bool Raster::isInRect(int2 point){
	if(point.getX() >= 0 && point.getX() <= this->iWidth && point.getY() >= 0 && point.getY() <= iHeight){
		return true;
	}else{
		return false;
	}
}

void Raster::clear(){
	int tmp = this->getBufferSize();
	memset(this->pBuffer, 0, this->getBufferSize());
}

uint* Raster::getBuffer(){
	return this->pBuffer;
}

int Raster::getBufferSize(){
	return (this->iWidth * this->iHeight * sizeof(Pixel));	// sizeof(Pixel) need 4 byte
}