#include "MotionActuator.h"

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, int newDX, int newDY) :
	object(s), DX(newDX), DY(newDY), condition("both")
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, double newAngle, double newForce, std::string con) :
	object(s), force(newForce), angle(newAngle), condition(con)
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, int newDT, std::string con) :
	object(s), DT(newDT), condition(con)
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, std::string con) :
	object(s), condition(con)
{
	this->name = n;
}

void MotionActuator::run()
{
	if (condition == "both")
	{
		object->setDX(DX);
		object->setDY(DY);
	}
	else if (condition == "x")
	{
		object->setDX(DT);
	}
	else if (condition == "y")
	{
		object->setDY(DT);
	}
	else if (condition == "flip")
	{
		object->setDX(-object->getDX());
		object->setDY(-object->getDY());
	}
	else if (condition == "flipx")
	{
		object->setDX(-object->getDX());
	}
	else if (condition == "flipy")
	{
		object->setDY(-object->getDY());
	}
	else if (condition == "multiply")
	{
		object->setDX(object->getDX() * DT);
		object->setDY(object->getDY() * DT);
	}
	else if (condition == "force")
	{
		object->addForce(angle, force);
	}
}

MotionActuator::~MotionActuator()
{
}
