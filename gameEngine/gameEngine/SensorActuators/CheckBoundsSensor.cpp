#include "CheckBoundsSensor.h"

CheckBoundsSensor::CheckBoundsSensor(AbstractSprite* s, int w, int h) :
	sprite(s), screenW(w), screenH(h)
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


CheckBoundsSensor::~CheckBoundsSensor()
{
}
