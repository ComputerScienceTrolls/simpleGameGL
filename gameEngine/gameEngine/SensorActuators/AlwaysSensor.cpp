#include "AlwaysSensor.h"

AlwaysSensor::AlwaysSensor()
{
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
