#include "AbstractObserver.h"

void AbstractObserver::setName(std::string newName)
{
	this->name = newName;
}

std::string AbstractObserver::getName()
{
	return this->name;
}
