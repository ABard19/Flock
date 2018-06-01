#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include<Pvector.h>
#include "Vehicle.h"

class VehicleSystem
{
public:
	vector<Vehicle> group;
	//Constructor
	VehicleSystem(){}

	int getSize()const;
	Vehicle getVehicle(int i);

	//Flock functions
	void addVehicle(Vehicle b);
	void Signal();
	int vCount();

	//Create Vehicle
	void CreateVehicle(float x, float y);

	//Modify Parameters
	void addDesSep();
	void subDesSep();
	void addDesAli();
	void subDesAli();
	void addDesCoh();
	void subDesCoh();

	void addSepW();
	void subSepW();
	void addAliW();
	void subAliW();
	void addCohW();
	void subCohW();
};
