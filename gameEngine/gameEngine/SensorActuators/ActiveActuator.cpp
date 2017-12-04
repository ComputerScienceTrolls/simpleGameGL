#include "ActiveActuator.h"

ActiveActuator::ActiveActuator(std::string n, AbstractSprite * s, bool con) :
	sprite(s), state(con)
{
	this->name = n;
}

void ActiveActuator::run()
{
	if (state)
	{
		sprite->setActive(true);
	}
	else
	{
		sprite->setActive(false);
	}
}

ActiveActuator::~ActiveActuator()
{
}
