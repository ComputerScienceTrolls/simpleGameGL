#include "VisibilityActuator.h"



VisibilityActuator::VisibilityActuator(AbstractSprite *s, bool con) :
	sprite(s), state(con)
{
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
