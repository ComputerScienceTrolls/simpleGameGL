#include "AbstractActuator.h"



AbstractActuator::AbstractActuator()
{
}

std::string AbstractActuator::getName()
{
	return this->name;
}

void AbstractActuator::setName(std::string newName)
{
	this->name = newName;
}

AbstractActuator::~AbstractActuator()
{
}
