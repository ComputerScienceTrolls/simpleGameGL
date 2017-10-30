#include "MotionActuator.h"

MotionActuator::MotionActuator(AbstractSprite *s, int newDX, int newDY) :
	sprite(s), DX(newDX), DY(newDY), condition("both"), DT(0)
{
}

MotionActuator::MotionActuator(AbstractSprite *s, int newDT, std::string con) :
	sprite(s), DT(newDT), condition(con)
{
}

MotionActuator::MotionActuator(AbstractSprite *s, std::string con) : 
	sprite(s), condition(con), DT(0)
{
}

void MotionActuator::run()
{
	if (condition == "both")
	{
		sprite->setDX(DX);
		sprite->setDY(DY);
	}
	else if (condition == "x")
	{
		sprite->setDX(DT);
	}
	else if (condition == "y")
	{
		sprite->setDY(DT);
	}
	else if (condition == "flipx")
	{
		sprite->setDX(-sprite->getDX());
	}
	else if (condition == "flipy")
	{
		sprite->setDY(-sprite->getDY());
	}
	else if (condition == "multiply")
	{
		sprite->setVelocity(glm::vec2(sprite->getDX() * DT, sprite->getDY() * DT));
	}
	else if (condition == "flip")
	{
		sprite->setDX(-sprite->getDX());
		sprite->setDY(-sprite->getDY());
	}
}

MotionActuator::~MotionActuator()
{
}
