#include "CollisionSensor.h"

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *first, AbstractSprite *second) :
	one(first), two(second)
{
	this->name = n;
}

void CollisionSensor::sense()
{
	if (one->collide(two))
	{
		for (int i = 0; i < actuators.size(); i++)
		{
			actuators.at(i)->run();
		}
	}
}

CollisionSensor::~CollisionSensor()
{
}
