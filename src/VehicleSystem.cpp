#include "Vehicle.h"
#include"VehicleSystem.h"


int VehicleSystem::getSize() const 
{ 
	return group.size(); 
}

Vehicle VehicleSystem::getVehicle(int i) 
{ 
	return group[i]; 
}


void VehicleSystem::addVehicle(Vehicle b) 
{
	group.push_back(b); 
}

int VehicleSystem::vCount()
{
	int count = 0;
	for (int i = 0; i < group.size(); i++)
	{
			count++;
	}
	return count;
}

void VehicleSystem::addDesSep()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesSep(1);
	}
}

void VehicleSystem::subDesSep()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesSep(-1);
	}
}

void VehicleSystem::addDesAli()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesAli(1);
	}
}

void VehicleSystem::subDesAli()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesAli(-1);
	}
}

void VehicleSystem::addDesCoh()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesCoh(1);
	}
}

void VehicleSystem::subDesCoh()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setDesCoh(-1);
	}
}

void VehicleSystem::addSepW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setSepW(.1);
	}
}

void VehicleSystem::subSepW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setSepW(-.1);
	}
}

void VehicleSystem::addAliW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setAliW(.1);
	}
}

void VehicleSystem::subAliW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setAliW(-.1);
	}
}

void VehicleSystem::addCohW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setCohW(.1);
	}
}

void VehicleSystem::subCohW()
{
	for (int i = 0; i < group.size(); i++)
	{
		group[i].setCohW(-.1);
	}
}

void VehicleSystem::Signal()
{
	for (int i = 0; i < group.size(); i++)
	{
		//Only checks in a certain range instead of checking through the whole flock in an attempt to reduce time complexity
		for (int j = 0; j < group.size(); j++)
		{
			if (group[i].location.distance(group[j].location) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
			{
				group[i].Direct(group);
			}
		}
	}
}

