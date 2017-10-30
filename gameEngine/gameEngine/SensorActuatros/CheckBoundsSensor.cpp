#include "CheckBoundsSensor.h"



CheckBoundsSensor::CheckBoundsSensor(AbstractSprite* s, int w, int h) :
	sprite(s), screenW(w), screenH(h)
{
}

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

void CheckBoundsSensor::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}


CheckBoundsSensor::~CheckBoundsSensor()
{
}
