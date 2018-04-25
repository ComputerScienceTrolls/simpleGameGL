#include "MotionActuator.h"
#include <math.h>

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newDX, float newDY) :
	object(s), DX(newDX), DY(newDY), condition("both"), conditionEnum(cBoth)
{
	this->name = n;
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newAngle, float newForce, std::string con) :
	object(s), force(newForce), angle(newAngle), condition(con), conditionEnum(cForce)
{
	this->name = n;

	if (condition != "force")
	{
		std::cout << "error in Motion Actuator, conditon: " << condition << " not supported under given parameters given, condition usually force, if your trying to add a condition make sure to add it to MotionActuator.cpp";
	}
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, float newDT, std::string con) :
	object(s), DT(newDT), condition(con), force(newDT)
{
	this->name = n;

	if (condition == "x")
	{
		conditionEnum = cX;
	}
	else if (condition == "y")
	{
		conditionEnum = cY;
	}
	else if (condition == "multiply")
	{
		conditionEnum = cMultiply;
	}
	else if (condition == "changeByX")
	{
		conditionEnum = cChangeByX;
	}
	else if (condition == "changeByY")
	{
		conditionEnum = cChangeByY;
	}
	else if (condition == "rotate")
	{
		conditionEnum = cRotate;
	}
	else if (condition == "rotateBy")
	{
		conditionEnum = cRotateBy;
	}
	else if (condition == "forceForward")
	{
		conditionEnum = cForceForward;
	}
	else
	{
		std::cout << "error in Motion Actuator: " << this->name << " conditon not found: " << condition;
	}
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *m, float dis, float speed, SceneObject *o, std::string con) :
	object(m), condition(con), distance(dis), force(speed), anotherObject(o), conditionEnum(cFollowObject)
{
	this->name = n;

	if (condition != "followObject")
	{
		std::cout << "error in Motion Actuator, conditon: " << condition << " not supported under given parameters given, if your trying to add a condition make sure to add it to MotionActuator.cpp";
	}
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *o, float s, SceneObject *ao):
	force(s), anotherObject(ao), object(o), condition("forceTowards"), conditionEnum(cForceTowards)
{
	this->name = n;

	if (condition != "forceTowards")
	{
		std::cout << "error in Motion Actuator, conditon: " << condition << " not supported under given parameters given, if your trying to add a condition make sure to add it to MotionActuator.cpp";
	}
}

MotionActuator::MotionActuator(std::string n, ObjectPoolActuator *op, float speed, SceneObject *ao):
	force(speed), anotherObject(ao), objectPool(op), condition("forceTowardsPool"), conditionEnum(cForceTowardPool)
{
	this->name = n;

	if (condition != "forceTowardPool")
	{
		std::cout << "error in Motion Actuator, conditon: " << condition << " not supported under given parameters given, if your trying to add a condition make sure to add it to MotionActuator.cpp";
	}
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, SceneObject *ao, std::string con = "angleTo") :
	object(s), anotherObject(ao), condition(con)
{
	this->name = n;

	if (condition == "angleTo")
	{
		conditionEnum = cAngleTo;
	}
	else if (condition == "setInFront")
	{
		conditionEnum = cSetInFront;
	}
	else
	{
		std::cout << "error in Motion Actuator, conditon: " << condition << " not supported under given parameters given, if your trying to add a condition make sure to add it to MotionActuator.cpp";
	}
}

MotionActuator::MotionActuator(std::string n, MovingSceneObject *s, std::string con) :
	object(s), condition(con)
{
	this->name = n;

	if (condition == "flip")
	{
		conditionEnum = cFlip;
	}
	else if (condition == "flipx" || condition == "flipX")
	{
		conditionEnum = cFlipX;
	}
	else if (condition == "flipy" || condition == "flipY")
	{
		conditionEnum = cFlipY;
	}
	else
	{
		std::cout << "error in Motion Actuator: " << this->name << " condition not found: " << condition;
	}
}

void MotionActuator::run()
{
	switch (conditionEnum)
	{
	case cBoth:
		object->setDX(DX);
		object->setDY(DY);
		break;
	case cX:
		object->setDX(DT);
		break;
	case cY:
		object->setDY(DT);
		break;
	case cFlip:
		object->setDX(-object->getDX());
		object->setDY(-object->getDY());
		break;
	case cFlipX:
		object->setDX(-object->getDX());
		break;
	case cFlipY:
		object->setDY(-object->getDY());
		break;
	case cMultiply:
		object->setDX(object->getDX() * DT);
		object->setDY(object->getDY() * DT);
		break;
	case cChangeByX:
		object->changeXBy(DT);
		break;
	case cChangeByY:
		object->changeYBy(DT);
		break;
	case cRotate:
		object->setRotation(DT);
		object->setMoveAngle(DT);
		break;
	case cRotateBy:
		object->setRotation(object->getRotation() + DT);
		object->setMoveAngle(object->getMoveAngle() + DT);
		break;
	case cAngleTo:
		object->setRotation(anotherObject->getRotation());
		break;
	case cForce:
		object->addForce(angle, force);
		break;
	case cForceForward:
	{
		double degrees = object->getRotation() * (180 / 3.141592653589793238463) - 180;
		object->addForce(float(degrees), force);
		break;
	}
	case cFollowObject:
		object->followObject(anotherObject, distance, force);
		break;
	case cForceTowards:
	{
		double degrees = anotherObject->getRotation() * double((180 / 3.141592653589793238463));
		object->addForce(float(degrees + 180), force);
		break;
	}
	case cForceTowardPool:
	{
		double degrees = double(anotherObject->getRotation()) * (180 / 3.141592653589793238463);
		dynamic_cast<AbstractSprite*>(objectPool->getCurrentObject())->addForce(float(degrees) + 180, force);
		break;
	}
	case cSetInFront:
	{
		double degrees = double(object->getRotation()) * (180 / 3.141592653589793238463);
		float h = object->getHeight();
		anotherObject->setPosition(degrees + 180, object->getPosition(),int(h));
		break;
	}
	default:
		break;
	}
	/*
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
	else if (condition == "forceTowardsPool")
	{
		double degrees = double(anotherObject->getRotation()) * (180 / 3.141592653589793238463);
		dynamic_cast<AbstractSprite*>(objectPool->getCurrentObject())->addForce(float(degrees) + 180, force);
	}
	else if (condition == "")
	{

	}
	*/
}

MotionActuator::~MotionActuator()
{
}
