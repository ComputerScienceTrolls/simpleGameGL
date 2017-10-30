#include "CollisionSensor.h"

CollisionSensor::CollisionSensor(AbstractSprite *first, AbstractSprite *second) :
	one(first), two(second)
{
	
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

void CollisionSensor::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}


CollisionSensor::~CollisionSensor()
{
}
