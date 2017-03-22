#ifndef _Math_H_
#define _Math_H_

#include <cmath>

typedef unsigned int uint;

template<class T>
class Matrix3x3;

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

template<class T>
class Vector3{
private:
	T tX, tY, tZ;

public:

	Vector3::Vector3(T x = 0, T y = 0, T z = 0) : tX(x), tY(y), tZ(z) {

	}

	~Vector3(){

	};

	T getX() const{
		return this->tX;
	}

	T getY() const{
		return this->tY;
	}

	T getZ() const{
		return this->tZ;
	}

	void setX(T x){
		this->tX = x;
	}

	void setY(T y){
		this->tY = y;
	}

	void setZ(T z){
		this->tZ = z;
	}

	Vector3<T>& operator*=(Matrix3x3<T>& matrix){
		Vector3<T> tmp[3];

		for(int i = 0; i < 3; i++){
			tmp[i] = matrix.getValue(i);
		}

		this->tX = this->getX() * tmp[0].getX() + this->getY() * tmp[1].getX() + this->getZ() * tmp[2].getX();
		this->tY = this->getX() * tmp[0].getY() + this->getY() * tmp[1].getY() + this->getZ() * tmp[2].getY();
		this->tZ = this->getX() * tmp[0].getZ() + this->getY() * tmp[1].getZ() + this->getZ() * tmp[2].getZ();

		return *this;
	}

private:

};

typedef Vector3<float> float3;

template<class T>
class Matrix3x3{
private:
	Vector3<T> value[3];

public:

	Matrix3x3::Matrix3x3() {

	}

	void translate(T x, T y){
		this->value[0] = Vector3<T>(T(1), T(0), T(0));
		this->value[1] = Vector3<T>(T(0), T(1), T(0));
		this->value[2] = Vector3<T>(T(x), T(y), T(1));
	}

	Vector3<T> getValue(int row){
		return this->value[row];
	}
};

typedef Matrix3x3<float> matrix3;

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