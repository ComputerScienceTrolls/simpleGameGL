#include "AbstractSensor.h"

AbstractSensor::AbstractSensor()
{
}

void AbstractSensor::setName(std::string newName)
{
	this->name = newName;
}

std::string AbstractSensor::getName()
{
	return this->name;
}

void AbstractSensor::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}

void AbstractSensor::removeActuator(AbstractActuator *act)
{
	int index = -1;
	for (int i = 0; i < this->actuators.size(); i++)
	{
		if (this->actuators[i] == act)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting" << this->actuators.at(index)->getName();
		this->actuators.erase(actuators.begin() + index);
	}
	else
	{
		std::cout << "actuator set to be removed " << actuators[index]->getName() << " not found";
	}
}

void AbstractSensor::removeActuator(std::string n)
{
	int index = -1;
	for (int i = 0; i < this->actuators.size(); i++)
	{
		if (this->actuators[i]->getName() == name)
		{
			index = i;
		}
	}

	//if found remove it from the vector
	if (index != -1)
	{
		std::cout << "deleting" << this->actuators.at(index)->getName();
		this->actuators.erase(actuators.begin() + index);
	}
	else
	{
		std::cout << "actuator set to be removed " << n << " not found";
	}
}

void AbstractSensor::removeActuator(int index)
{
	if (index > -1 && index <= actuators.size() - 1)
	{
		this->actuators.erase(actuators.begin() + index);
	}
	else
	{
		std::cout << "index is not in range";
	}
}

AbstractSensor::~AbstractSensor()
{
}
