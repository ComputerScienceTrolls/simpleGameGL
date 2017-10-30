#include "ActiveActuator.h"

ActiveActuator::ActiveActuator(AbstractSprite * s, bool con) :
	sprite(s), state(con)
{
}

void ActiveActuator::run()
{
	if (state)
	{
		sprite->setState("active", true);
	}
	else
	{
		sprite->setState("active", false);
	}
}

ActiveActuator::~ActiveActuator()
{
}
