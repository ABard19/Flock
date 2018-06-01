#include "VehicleSystem.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Simulation
{
private:
	sf::RenderWindow field;
	int field_width;
	int field_height;

	VehicleSystem cohort;
	float vsize;
	vector<sf::CircleShape> shapes;

	void createVehicle(float x, float y);
	void Input();
	void Render(float fps);

public:
	Simulation();
	void DM();

};