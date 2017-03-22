#include "Pixel.h"

bool operator!=(const Pixel& left,const Pixel& right){
	return left.getR() != right.getR() || left.getG() != right.getG() || left.getB() != right.getB() || left.getA() != right.getA();
}

Pixel operator+(const Pixel& left,const Pixel& right){
	Pixel pixel;
	pixel.setR(left.getR() * right.getR());
	pixel.setG(left.getG() * right.getG());
	pixel.setB(left.getB() * right.getB());
	pixel.setA(left.getA() * right.getA());

	return pixel;
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : ucR(r), ucG(g), ucB(b), ucA(a){

}

Pixel::Pixel(uint pixel){
	this->uiColor = pixel;
}

Pixel Pixel::Interpolation(const Pixel& start, const Pixel& end, float percentage){
	Pixel pixel;
	pixel.ucR = (unsigned char)(start.ucR + percentage * (end.ucR - start.ucR));
	pixel.ucG = (unsigned char)(start.ucG + percentage * (end.ucG - start.ucG));
	pixel.ucB = (unsigned char)(start.ucB + percentage * (end.ucB - start.ucB));
	pixel.ucA = (unsigned char)(start.ucA + percentage * (end.ucA - start.ucA));

	return pixel;
}

float2 Pixel::Interpolation(const float2& start, const float2& end, float percentage){
	float2 uv;
	uv.setX((start.getX() + percentage * (end.getX() - start.getX())));
	uv.setY((start.getY() + percentage * (end.getY() - start.getY())));

	return uv;
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

uint Pixel::getColor(){
	return this->uiColor;
}

void Pixel::setR(unsigned char r){
	this->ucR = r;
}

void Pixel::setG(unsigned char g){
	this->ucG = g;
}

void Pixel::setB(unsigned char b){
	this->ucB = b;
}

void Pixel::setA(unsigned char a){
	this->ucA = a;
}
