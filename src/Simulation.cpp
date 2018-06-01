#include "VehicleSystem.h"
#include "Simulation.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Simulation::Simulation()
{
	this->field_height = 800;
	this->field_width = 640;
	this->field.create(sf::VideoMode(field_width, field_height), "Flock Off");
}

void Simulation::DM()
{
	for (int i = 0; i < 10; i++)
	{
		createVehicle(field_width / 2, field_height / 2);
	}


		sf::Clock clock;
		while (field.isOpen())
		{
			float currentTime = clock.restart().asSeconds();
			float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
			Input();
			Render(fps);
		}
}

void Simulation::Input()
{
	sf::Event event;
	while (field.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			field.close();
		}

		// Event to create new "prey" boids
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) 
		{
			createVehicle(rand() % field_width, rand() % field_height);
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		{
			cohort.addDesSep();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			cohort.subDesSep();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
		{
			cohort.addDesAli();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			cohort.subDesAli();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
		{
			cohort.addDesCoh();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
		{
			cohort.subDesCoh();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::I)
		{
			cohort.addSepW();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::J)
		{
			cohort.subSepW();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::O)
		{
			cohort.addAliW();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K)
		{
			cohort.subAliW();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		{
			cohort.addCohW();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L)
		{
			cohort.subCohW();
		}

	}
}

void Simulation::createVehicle(float x, float y)
{
	int size = rand() % 10 - 2;
	Vehicle v(x, y);
	sf::CircleShape shape(size, 3);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(.5);
	cohort.addVehicle(v);
	shapes.push_back(shape);
	// New Shape is drawn
	field.draw(shapes[shapes.size() - 1]);
}

void Simulation::Render(float fps)
{
	field.clear();
	for (int i = 0; i < shapes.size(); i++)
	{
		field.draw(shapes[i]);
		shapes[i].setPosition(cohort.getVehicle(i).location.x, cohort.getVehicle(i).location.y);
		float theta = cohort.getVehicle(i).getAngle(cohort.getVehicle(i).velocity);
		shapes[i].setRotation(theta);
		if (shapes[i].getPosition().x > field_width)
		{
			shapes[i].setPosition(shapes[i].getPosition().x - field_width, shapes[i].getPosition().y);
		}
		// If boid exits bottom boundary
		if (shapes[i].getPosition().y > field_height)
		{
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - field_height);
		}
		// If boid exits left boundary
		if (shapes[i].getPosition().x < 0)
		{
			shapes[i].setPosition(shapes[i].getPosition().x + field_width, shapes[i].getPosition().y);
		}
		// If boid exits top boundary
		if (shapes[i].getPosition().y < 0)
		{
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + field_height);
		}
	}
	cohort.Signal();
	field.display();
}