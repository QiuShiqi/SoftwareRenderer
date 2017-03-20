#include "Edge.h"
#include "Math.h"

Edge::Edge(int startX, int startY, int endX, int endY, Pixel pixelStart, Pixel pixelEnd){

	if(startY < endY){
		this->iStartX = startX;
		this->iStartY = startY;

		this->iEndX = endX;
		this->iEndY = endY;

		this->pixelStart = pixelStart;
		this->pixelEnd = pixelEnd;

	}else{
		this->iStartX = endX;
		this->iStartY = endY;

		this->iEndX = startX;
		this->iEndY = startY;

		this->pixelStart = pixelEnd;
		this->pixelEnd = pixelStart;
	}
}

int Edge::getStartX(){
	return this->iStartX;
}

int Edge::getStartY(){
	return this->iStartY;
}

int Edge::getEndX(){
	return this->iEndX;
}

int Edge::getEndY(){
	return this->iEndY;
}

Pixel Edge::getPixelStart(){
	return this->pixelStart;
}

Pixel Edge::getPixelEnd(){
	return this->pixelEnd;
}