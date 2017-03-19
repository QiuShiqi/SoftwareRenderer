#ifndef _Math_H_
#define _Math_H_

template<class T>
class Vector2{
private:
	T tX, tY;

public:
	Vector2::Vector2(T x, T y) : tX(x), tY(y){

	}

	~Vector2(){

	};

	T getX(){
		return this->tX;
	}

	T getY(){
		return this->tY;
	}
};

typedef Vector2<float> float2;

class Base{
public:

	template<class T>
	static T getMin(T a, T b){
		return a < b ? a : b;
	}

	template<class T>
	static T getMax(T a, T b){
		return a > b ? a : b;
	}

	template<class T>
	static T getAbs(T a){
		return a > 0 ? a : -a;
	}

};

#endif _Math_H_