#include<Vehicle.h>
#include <cmath>
#include <vector>
#include "SFML/Window.hpp"

const int window_height = 640;
const int window_width = 800;

Vehicle::Vehicle(float x, float y)
{
	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2);
	location = Pvector(x, y);
	maxSpeed = 1.5;
	maxForce = 0.25;
	
	desSep = 10;
	desAli = 35;
	desCoh = 12;
	SepW = 0.75;
	AliW = 0.5;
	CohW = 0.5;
}

void Vehicle::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

Pvector Vehicle::Seek(Pvector target)
{
	Pvector desired;
	desired.subVector(target);  // A vector pointing from the location to the target
	desired.normalize();		// Normalize desired and scale to maximum speed
	desired.mulScalar(maxSpeed);
	acceleration.subTwoVector(desired, velocity); // Steering = Desired minus Velocity
	acceleration.limit(maxForce);				 // Limit to maximum steering force
	return acceleration;
}

void Vehicle::Update()
{
	acceleration.mulScalar(.35); 		//To make the slow down not as abrupt
	velocity.addVector(acceleration);	// Update velocity
	velocity.limit(maxSpeed);			// Limit speed
	location.addVector(velocity);
	acceleration.mulScalar(0);			// Reset accelertion to 0 each cycle
}

float Vehicle::getDesSep() const 
{ 
	return desSep; 
}

float Vehicle::getDesAli() const 
{ 
	return desAli; 
}

float Vehicle::getDesCoh() const 
{ 
	return desCoh; 
}

float Vehicle::getSepW() const 
{ 
	return SepW; 
}

float Vehicle::getAliW() const 
{ 
	return AliW; 
}

float Vehicle::getCohW() const 
{ 
	return CohW; 
}

void Vehicle::setDesSep(float x) 
{ 
	desSep += x; 
}

void Vehicle::setDesAli(float x) 
{ 
	desAli += x; 
}

void Vehicle::setDesCoh(float x) 
{
	desCoh += x; 
}

void Vehicle::setSepW(float x) 
{ 
	SepW += x; 
}

void Vehicle::setAliW(float x) 
{ 
	AliW += x; 
}

void Vehicle::setCohW(float x) 
{ 
	CohW += x; 
}

float Vehicle::getAngle(Pvector v) const
{
	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / 3.1459f);
	return angle;
}

void Vehicle::Wrap()
{
	if (location.x < 0)    location.x += window_width;
	if (location.y < 0)    location.y += window_height;
	if (location.x > window_width) location.x -= window_width;
	if (location.y > window_height) location.y -= window_height;
}

// This applies the behaviours updates data, and wraps around the window
void Vehicle::Direct(vector <Vehicle> v)
{
	flock(v);
	Update();
	Wrap();
}

// Applies the three laws to the flock of boids
void Vehicle::flock(vector<Vehicle> v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(SepW);
	ali.mulScalar(AliW); // Might need to alter weights for different characteristics
	coh.mulScalar(CohW);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}


Pvector Vehicle::Separation(vector<Vehicle> Vehicles)
{
	float desiredseparation = desSep;
	Pvector steer(0, 0);
	int count = 0;
	for (int i = 0; i < Vehicles.size(); i++)
	{
		float dist = location.distance(Vehicles[i].location);
		if ((dist > 0) && (dist < desiredseparation))
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, Vehicles[i].location);
			diff.normalize();
			diff.divScalar(dist);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
	}
	if (count > 0)
	{
		steer.divScalar(static_cast<float>(count));
	}
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

Pvector Vehicle::Alignment(vector<Vehicle> Vehicles)
{
	float neighbordist = desAli; // Field of vision

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Vehicles.size(); i++) 
	{
		float d = location.distance(Vehicles[i].location);

		if ((d > 0) && (d < neighbordist)) 
		{ // 0 < d < 50
			sum.addVector(Vehicles[i].velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0)
	{
		sum.divScalar(static_cast<float>(count));// Divide sum by the number of close boids (average of velocity)
		sum.normalize();            // Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
									// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)
		steer.limit(maxForce);
		return steer;
	}
	else 
	{
		Pvector temp(0, 0);
		return temp;
	}
}

// Cohesion
// Finds the average location of nearby boids and manipulates the
// steering force to move in that direction.
Pvector Vehicle::Cohesion(vector<Vehicle> Vehicles)
{
	float neighbordist = desCoh;
	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Vehicles.size(); i++) 
	{
		float d = location.distance(Vehicles[i].location);

		if ((d > 0) && (d < neighbordist)) 
		{
			sum.addVector(Vehicles[i].location);
			count++;
		}
	}
	if (count > 0) 
	{
		sum.divScalar(count);
		return Seek(sum);
	}
	else 
	{
		Pvector temp(0, 0);
		return temp;
	}
}