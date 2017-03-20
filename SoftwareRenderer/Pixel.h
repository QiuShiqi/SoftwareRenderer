#ifndef _Pixel_H_
#define _Pixel_H_

class Pixel{
public:
	unsigned char cB, cG, cR, cA;	// windows下R和B相反

public:
	Pixel(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
	static Pixel Interpolation(Pixel start, Pixel end, float percentage);	// 插值计算
};

#endif