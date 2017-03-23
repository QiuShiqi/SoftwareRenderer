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

private:

};

typedef Vector3<float> float3;

template<class T>
class Matrix3x3{
private:
	Vector3<T> value[3];

public:

	Matrix3x3(){

	}

	Matrix3x3(Vector3<T> row0, Vector3<T> row1, Vector3<T> row2) {
		this->value[0] = row0;
		this->value[1] = row1;
		this->value[2] = row2;
	}

	void setValue(int row, Vector3<T> value){
		this->value[row] = value;
	}

	void translate(T x, T y){
		this->value[0] = Vector3<T>(T(1), T(0), T(0));
		this->value[1] = Vector3<T>(T(0), T(1), T(0));
		this->value[2] = Vector3<T>(T(x), T(y), T(1));
	}

	void scale(T x, T y){
		this->value[0] = Vector3<T>(T(x), T(0), T(0));
		this->value[1] = Vector3<T>(T(0), T(y), T(0));
		this->value[2] = Vector3<T>(T(0), T(0), T(1));
	}

	void rotate(T angle){
		T rad = Math::deg2rad(angle);
		T c = cos(rad);
		T s = sin(rad);

		this->value[0] = Vector3<T>(T(c), T(-s), T(0));
		this->value[1] = Vector3<T>(T(s), T(c), T(0));
		this->value[2] = Vector3<T>(T(0), T(0), T(1));
	}

	Vector3<T> operator*(const Vector3<T>& vector3){

		T x = vector3.getX() * this->value[0].getX() + vector3.getY() * this->value[1].getX() + vector3.getZ() * this->value[2].getX();
		T y = vector3.getX() * this->value[0].getY() + vector3.getY() * this->value[1].getY() + vector3.getZ() * this->value[2].getY();
		T z = vector3.getX() * this->value[0].getZ() + vector3.getY() * this->value[1].getZ() + vector3.getZ() * this->value[2].getZ();

		return Vector3<T>(x, y, z);
	}

	Matrix3x3<T> operator*(const Matrix3x3<T>& matrix3x3){
		Vector3<T> tmp[3];
		for(int i = 0; i < 3; i++){
			tmp[i] = matrix3x3.getValue(i);
		}

		T x0 = tmp[0].getX() * this->value[0].getX() + tmp[1].getX() * this->value[0].getY() + tmp[2].getX() * this->value[0].getZ();
		T y0 = tmp[0].getY() * this->value[0].getX() + tmp[1].getY() * this->value[0].getY() + tmp[2].getY() * this->value[0].getZ();
		T z0 = tmp[0].getZ() * this->value[0].getX() + tmp[1].getZ() * this->value[0].getY() + tmp[2].getZ() * this->value[0].getZ();

		T x1 = tmp[0].getX() * this->value[1].getX() + tmp[1].getX() * this->value[1].getY() + tmp[2].getX() * this->value[1].getZ();
		T y1 = tmp[0].getY() * this->value[1].getX() + tmp[1].getY() * this->value[1].getY() + tmp[2].getY() * this->value[1].getZ();
		T z1 = tmp[0].getZ() * this->value[1].getX() + tmp[1].getZ() * this->value[1].getY() + tmp[2].getZ() * this->value[1].getZ();

		T x2 = tmp[0].getX() * this->value[2].getX() + tmp[1].getX() * this->value[2].getY() + tmp[2].getX() * this->value[2].getZ();
		T y2 = tmp[0].getY() * this->value[2].getX() + tmp[1].getY() * this->value[2].getY() + tmp[2].getY() * this->value[2].getZ();
		T z2 = tmp[0].getZ() * this->value[2].getX() + tmp[1].getZ() * this->value[2].getY() + tmp[2].getZ() * this->value[2].getZ();

		return Matrix3x3(Vector3<T>(x0, y0, z0), Vector3<T>(x1, y1, z1), Vector3<T>(x2, y2, z2));
	}

	Vector3<T> getValue(int row) const{
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