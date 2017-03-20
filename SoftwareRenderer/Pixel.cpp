#include "Pixel.h"

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : cR(r), cG(g), cB(b), cA(a){

}

Pixel::Pixel(uint pixel){
	this->uiColor = pixel;
}

Pixel Pixel::Interpolation(Pixel start, Pixel end, float percentage){
	Pixel pixel;

	pixel.cR = (unsigned char)(start.cR + percentage * (end.cR - start.cR));
	pixel.cG = (unsigned char)(start.cG + percentage * (end.cG - start.cG));
	pixel.cB = (unsigned char)(start.cB + percentage * (end.cB - start.cB));
	pixel.cA = (unsigned char)(start.cA + percentage * (end.cA - start.cA));

	return pixel;
}