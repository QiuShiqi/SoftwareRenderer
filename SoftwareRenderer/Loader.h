#ifndef _Loader_H_
#define _Loader_H_

#include "Image.h"

class Loader{
public:
	static Image* loadImage(const char* fileName);
};

#endif