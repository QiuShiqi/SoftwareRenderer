#ifndef _Pixel_H_
#define _Pixel_H_

#include "Math.h"

class Pixel{
	friend bool operator!=(const Pixel& left,const Pixel& right);
	friend Pixel operator+(const Pixel& left,const Pixel& right);

private:
	union{
		struct  
		{
			unsigned char ucB, ucG, ucR, ucA;	// Under the Windows system, R and B is opposite
		};
		uint uiColor;
	};

public:
	Pixel(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
	Pixel(uint pixel);

	// Interpolation calculation
	static Pixel Interpolation(const Pixel& start, const Pixel& end, float percentage);	
	static float2 Interpolation(const float2& start, const float2& end, float percentage);

	unsigned char getR() const;
	unsigned char getG() const;
	unsigned char getB() const;
	unsigned char getA() const;
	uint getColor();

	void setR(unsigned char r);
	void setG(unsigned char g);
	void setB(unsigned char b);
	void setA(unsigned char a);
};

#endif