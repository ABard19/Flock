#pragma once
#include<Pvector.h>
#include <SFML/Graphics.hpp>

class Vehicle 
{
public:
	Pvector location;
	Pvector velocity;
	Pvector acceleration;

	float maxSpeed=5.0f;
	float maxForce=1.25f;

	float desSep;
	float desAli;
	float desCoh;
	float SepW;
	float AliW;
	float CohW;

	Vehicle(float x, float y);

	void applyForce(Pvector force);

	Pvector Seek(Pvector target);

	void Update();
	void Wrap();

	float getAngle(Pvector v)const;

	void flock(vector<Vehicle> Vehicles);
	void Direct(vector<Vehicle> Vehicles);

	//Behaviours

	Pvector Separation(vector<Vehicle> Vehicles);
	Pvector Cohesion(vector<Vehicle> Vehicles);
	Pvector Alignment(vector<Vehicle> Vehicles);

	float getDesSep() const;
	float getDesAli() const;
	float getDesCoh() const;
	float getSepW() const;
	float getAliW() const;
	float getCohW() const;

	void setDesSep(float x);
	void setDesAli(float x);
	void setDesCoh(float x);
	void setSepW(float x);
	void setAliW(float x);
	void setCohW(float x);
};