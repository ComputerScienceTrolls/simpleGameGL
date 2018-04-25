#include "AlwaysSensor.h"

AlwaysSensor::AlwaysSensor()
{
}

AlwaysSensor::AlwaysSensor(std::string n)
{
	this->name = n;
}

void AlwaysSensor::sense()
{
	for (int i = 0; i < actuators.size(); i++)
	{
		actuators.at(i)->run();
	}
}

AlwaysSensor::~AlwaysSensor()
{
}
