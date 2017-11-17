#include "CollisionSensor.h"

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *first, AbstractSprite *second) :
	name(n), one(first), two(second)
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

std::string CollisionSensor::getName()
{
	return this->name;
}

void CollisionSensor::setName(std::string newName)
{
	this->name = newName;
}


CollisionSensor::~CollisionSensor()
{
}
