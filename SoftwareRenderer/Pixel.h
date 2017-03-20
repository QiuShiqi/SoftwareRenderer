#ifndef _Pixel_H_
#define _Pixel_H_

typedef unsigned int uint;

class Pixel{
public:
	union{
		struct  
		{
			unsigned char cB, cG, cR, cA;	// Under the Windows system, R and B is opposite
		};
		uint uiColor;
	};

public:
	Pixel(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
	Pixel(uint pixel);

	static Pixel Interpolation(Pixel start, Pixel end, float percentage);	// Interpolation calculation
};

#endif