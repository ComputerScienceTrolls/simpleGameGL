#include "VisibilityActuator.h"

VisibilityActuator::VisibilityActuator(std::string n, AbstractSprite *s, bool con) :
	sprite(s), state(con)
{
	this->name = n;
}

void VisibilityActuator::run()
{
	if (state)
	{
		sprite->setState("visible", true);
	}
	else
	{
		sprite->setState("visible", false);
	}
}

VisibilityActuator::~VisibilityActuator()
{
}
