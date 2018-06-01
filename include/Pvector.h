#include <iostream>
#include<vector>
using namespace std;

#ifndef Pvector_H_
#define Pvector_H_

class Pvector
{
public:
	float x;
	float y;

	//Constructor
	Pvector(){}

	Pvector(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}

	void set(float x, float y);

	//Scalar functions. Scale a vector by a float value
	void addScalar(float a);
	void subScalar(float a);
	void mulScalar(float a);
	void divScalar(float a);

	//Vector functions. Vector math

	void addVector(Pvector v);
	void subVector(Pvector v);
	void mulVector(Pvector v);
	void divVector(Pvector v);

	//Calculations

	void limit(double max);
	float distance(Pvector v)const ;
	float dotProduct(Pvector v)const ;
	float magnitude() const;
	void setMagnitude(float a);
	float angleBetween(Pvector v) const;
	void normalize();
	static Pvector subTwoVector(Pvector v, Pvector v2);
	static Pvector copy(Pvector v);

	
};


#endif