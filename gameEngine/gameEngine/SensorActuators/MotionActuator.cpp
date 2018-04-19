#include "MotionActuator.h"
#include <math.h>

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newDX, float newDY) :
	object(s), DX(newDX), DY(newDY), condition("both")
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newAngle, float newForce, std::string con) :
	object(s), force(newForce), angle(newAngle), condition(con)
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newDT, std::string con) :
	object(s), DT(newDT), condition(con)
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string name, MovingSceneObject *m, float dis, float speed, SceneObject *o, std::string con) :
	object(m), condition(con), distance(dis), force(speed), anotherObject(o)
{
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *o, float s, SceneObject *ao):
	force(s), anotherObject(ao), object(o), condition("forceTowards")
{
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, SceneObject *ao) :
	object(s), anotherObject(ao), condition("angleTo")
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
	else if (condition == "changeByX")
	{
		object->changeXBy(DT);
	}
	else if (condition == "changeByY")
	{
		object->changeYBy(DT);
	}
	else if (condition == "rotate")
	{
		object->setRotation(DT);
		object->setMoveAngle(DT);
	}
	else if (condition == "rotateBy")
	{
		object->setRotation(object->getRotation() + DT);
		object->setMoveAngle(object->getMoveAngle() + DT);
	}
	else if (condition == "angleTo")
	{
		object->setRotation(anotherObject->getRotation());
	}
	else if (condition == "force")
	{
		object->addForce(angle, force);
	}
	else if (condition == "forceForward")
	{
		double degrees = object->getRotation() * (180 / 3.141592653589793238463) - 180;
		object->addForce(float(degrees), force);
	}
	else if (condition == "followObject")
	{
		object->followObject(anotherObject, distance, force);
	}
	else if (condition == "forceTowards")
	{
		float degrees = anotherObject->getRotation() * float((180 / 3.141592653589793238463));
		object->addForce(degrees + 180, force);
	}
}

MotionActuator::~MotionActuator()
{
}
