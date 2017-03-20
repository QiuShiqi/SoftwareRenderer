#include "Span.h"

Span::Span(int startX, int endX, int y, Pixel pixelStart, Pixel pixelEnd) : iY(y) {

	if(startX < endX){
		this->iStartX = startX;
		this->iEndX = endX;

		this->pixelStart = pixelStart;
		this->pixelEnd = pixelEnd;

	}else{
		this->iStartX = endX;
		this->iEndX = startX;

		this->pixelStart = pixelEnd;
		this->pixelEnd = pixelStart;
	}
}

int Span::getStartX() {
	return this->iStartX;
}

int Span::getEndX() {
	return this->iEndX;
}

int Span::getY() {
	return this->iY;
}

Pixel Span::getPixelStart(){
	return this->pixelStart;
}

Pixel Span::getPixelEnd(){
	return this->pixelEnd;
}