#include "Edge.h"
#include "Math.h"

Edge::Edge(float3 start, float3 end, Pixel pixelStart, Pixel pixelEnd, float2 startUV, float2 endUV){

	if(start.getY() < end.getY()){
		this->fStart = start;
		this->fStartUV = startUV;

		this->fEnd = end;
		this->fEndUV = endUV;

		this->pixelStart = pixelStart;
		this->pixelEnd = pixelEnd;

	}else{
		this->fStart = end;
		this->fStartUV = endUV;

		this->fEnd = start;
		this->fEndUV = startUV;

		this->pixelStart = pixelEnd;
		this->pixelEnd = pixelStart;
	}
}

float3 Edge::getStart(){
	return this->fStart;
}

float3 Edge::getEnd(){
	return this->fEnd;
}

Pixel Edge::getPixelStart(){
	return this->pixelStart;
}

Pixel Edge::getPixelEnd(){
	return this->pixelEnd;
}

float2 Edge::getUVStart(){
	return this->fStartUV;
}

float2 Edge::getUVEnd(){
	return this->fEndUV;
}
