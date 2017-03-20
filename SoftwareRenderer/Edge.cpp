#include "Edge.h"
#include "Math.h"

Edge::Edge(int startX, int startY, int endX, int endY){

	if(startY < endY){
		this->iStartX = startX;
		this->iStartY = startY;

		this->iEndX = endX;
		this->iEndY = endY;

	}else{
		this->iStartX = endX;
		this->iStartY = endY;

		this->iEndX = startX;
		this->iEndY = startY;
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
