#ifndef _Edge_H_
#define _Edge_H_

class Edge{
private:
	int iStartX, iStartY;
	int iEndX, iEndY;

public:
	Edge(int startX, int startY, int endX, int endY);

	int getStartX();
	int getStartY();
	int getEndX();
	int getEndY();
};

#endif