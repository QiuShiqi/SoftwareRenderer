#include "Pixel.h"

bool operator!=(const Pixel& left,const Pixel& right){
	return left.getR() != right.getR() || left.getG() != right.getG() || left.getB() != right.getB() || left.getA() != right.getA();
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : ucR(r), ucG(g), ucB(b), ucA(a){

}

Pixel::Pixel(uint pixel){
	this->uiColor = pixel;
}

Pixel Pixel::Interpolation(Pixel start, Pixel end, float percentage){
	Pixel pixel;

	pixel.ucR = (unsigned char)(start.ucR + percentage * (end.ucR - start.ucR));
	pixel.ucG = (unsigned char)(start.ucG + percentage * (end.ucG - start.ucG));
	pixel.ucB = (unsigned char)(start.ucB + percentage * (end.ucB - start.ucB));
	pixel.ucA = (unsigned char)(start.ucA + percentage * (end.ucA - start.ucA));

	return pixel;
}

unsigned char Pixel::getR() const{
	return this->ucB;
}

unsigned char Pixel::getG() const{
	return this->ucG;
}

unsigned char Pixel::getB() const{
	return this->ucR;
}

unsigned char Pixel::getA() const{
	return this->ucA;
}
