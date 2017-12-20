#include "CheckBoundsSensor.h"

CheckBoundsSensor::CheckBoundsSensor(std::string n, AbstractSprite* s, int w, int h) :
	sprite(s), screenW(w), screenH(h)
{
	this->name = n;
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

CheckBoundsSensor::~CheckBoundsSensor()
{
}
