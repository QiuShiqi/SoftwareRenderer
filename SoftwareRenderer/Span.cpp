#include "Span.h"

Span::Span(int startX, int endX, int y, Pixel pixelStart, Pixel pixelEnd, float2 startUV, float2 endUV) : iY(y) {

	if(startX < endX){
		this->iStartX = startX;
		this->iEndX = endX;
		
		this->pixelStart = pixelStart;
		this->pixelEnd = pixelEnd;

		this->fStartUV = startUV;
		this->fEndUV = endUV;

	}else{
		this->iStartX = endX;
		this->iEndX = startX;

		this->pixelStart = pixelEnd;
		this->pixelEnd = pixelStart;

		this->fStartUV = endUV;
		this->fEndUV = startUV;
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

float2 Span::getStartUV(){
	return this->fStartUV;
}

float2 Span::getEndUV(){
	return this->fEndUV;
}
