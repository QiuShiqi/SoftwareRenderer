#ifndef _Pixel_H_
#define _Pixel_H_

typedef unsigned int uint;

class Pixel{
	friend bool operator!=(const Pixel& left,const Pixel& right);
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

	static Pixel Interpolation(Pixel start, Pixel end, float percentage);	// Interpolation calculation
	
	unsigned char getR() const;
	unsigned char getG() const;
	unsigned char getB() const;
	unsigned char getA() const;
};

#endif