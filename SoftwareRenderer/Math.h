#ifndef _Math_H_
#define _Math_H_

#include <cmath>

typedef unsigned int uint;

template<class T>
class Vector2{
private:
	T tX, tY;

public:

	Vector2::Vector2(T x = 0, T y = 0) : tX(x), tY(y){

	}

	~Vector2(){

	};

	T getX() const{
		return this->tX;
	}

	T getY() const{
		return this->tY;
	}

	void setX(T x){
		this->tX = x;
	}

	void setY(T y){
		this->tY = y;
	}
};

typedef Vector2<float> float2;
typedef Vector2<int> int2;

class Math{
public:

	template<class T>
	static T getMin(T a, T b){
		return a <= b ? a : b;
	}

	template<class T>
	static T getMax(T a, T b){
		return a >= b ? a : b;
	}

	template<class T>
	static T getAbs(T a){
		return a >= 0 ? a : -a;
	}

	template<class T>
	static float deg2rad(T degree){
		return 0.01745329251994329 * degree;
	}

};

#endif _Math_H_