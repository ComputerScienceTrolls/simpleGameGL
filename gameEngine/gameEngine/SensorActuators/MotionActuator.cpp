#include "MotionActuator.h"

MotionActuator::MotionActuator(AbstractSprite *s, int newDX, int newDY) :
	sprite(s), DX(newDX), DY(newDY), condition("both")
{
}

MotionActuator::MotionActuator(AbstractSprite *s, double newAngle, double newForce, std::string con) :
	sprite(s), force(newForce), angle(newAngle), condition(con)
{
}

MotionActuator::MotionActuator(AbstractSprite *s, int newDT, std::string con) :
	sprite(s), DT(newDT), condition(con)
{
}

MotionActuator::MotionActuator(AbstractSprite *s, std::string con) :
	sprite(s), condition(con)
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
	else if (condition == "flip")
	{
		sprite->setDX(-sprite->getDX());
		sprite->setDY(-sprite->getDY());
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
		sprite->setDX(sprite->getDX() * DT);
		sprite->setDY(sprite->getDY() * DT);
	}
	else if (condition == "force")
	{
		sprite->addForce(angle, force);
	}
}

MotionActuator::~MotionActuator()
{
}
