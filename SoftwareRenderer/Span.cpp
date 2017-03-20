#include "Span.h"

Span::Span(int startX, int endX, int y) : iY(y) {

	if(startX < endX){
		this->iStartX = startX;
		this->iEndX = endX;

	}else{
		this->iStartX = endX;
		this->iEndX = startX;
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