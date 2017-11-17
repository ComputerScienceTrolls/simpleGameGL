#include "CheckBoundsSensor.h"

CheckBoundsSensor::CheckBoundsSensor(std::string n, AbstractSprite* s, int w, int h) :
	name(n), sprite(s), screenW(w), screenH(h)
{
}

//run sprite's checkbounds function with the given width and height, if return true run actuators
void CheckBoundsSensor::sense()
{
	if (sprite->checkBounds(screenW, screenH))
	{
		for (int i = 0; i < actuators.size(); i++)
		{
			actuators.at(i)->run();
		}
	}
}

//add actuator to be ran if sensed
void CheckBoundsSensor::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}

std::string CheckBoundsSensor::getName()
{
	return this->name;
}

void CheckBoundsSensor::setName(std::string n)
{
	this->name = n;
}


CheckBoundsSensor::~CheckBoundsSensor()
{
}
