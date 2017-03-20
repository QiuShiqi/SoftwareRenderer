#ifndef _Span_H_
#define _Span_H_

class Span{
private:
	int iStartX, iEndX, iY;

public:
	Span(int startX, int endX, int y);

	int getStartX();
	int getEndX();
	int getY();
};

#endif