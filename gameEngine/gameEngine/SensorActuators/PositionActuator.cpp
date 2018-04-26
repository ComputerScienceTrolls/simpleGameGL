#include "PositionActuator.h"

//constructor with a given x and y
PositionActuator::PositionActuator(std::string n, Sprite *s, int newX, int newY) :
	sprite(s), x(newX), y(newY), condition("both")
{
	this->name = n;
}

//constructor with a change and condition
PositionActuator::PositionActuator(std::string n, Sprite *s, int newD, std::string con) :
	sprite(s), d(newD), condition(con)
{
	this->name = n;
}

//constructor with only a condition
PositionActuator::PositionActuator(std::string n, Sprite *s, std::string con) :
	sprite(s), condition(con)
{
	this->name = n;
}

PositionActuator::PositionActuator(std::string n, SceneObject *o, SceneObject *t) :
	one(o), two(t), condition("set")
{
	this->name = n;
}

PositionActuator::PositionActuator(std::string n, ObjectPool<SceneObject> *objectPool, SceneObject *s) :
	OPSO(objectPool), two(s), condition("objectPoolSet")
{
	this->name = n;
}

PositionActuator::PositionActuator(std::string n, ObjectPool<Sprite> *objectPool, SceneObject *s) :
	OPS(objectPool), two(s), condition("objectPoolSet")
{
	this->name = n;
}

//run based on given or defaulted conditon, if both x and y given assume set to that new pos, if only x or y set it while retaining other not given axis, if flip condition set vertex to negative, always ending up offscreen
void PositionActuator::run()
{
	if (condition == "both")
	{
		sprite->setPosition(glm::vec2(x,y));
	}
	else if (condition == "x")
	{
		sprite->setPosition(glm::vec2(x,sprite->getPosition().y));
	}
	else if (condition == "y")
	{
		sprite->setPosition(glm::vec2(sprite->getPosition().x, y));
	}
	else if (condition == "flip")
	{
		sprite->setPosition(glm::vec2(-sprite->getPosition().x, -sprite->getPosition().y));
	}
	else if (condition == "set")
	{
		one->setPosX(two->getPosX() + two->getWidth()/2);
		one->setPosY(two->getPosY() + two->getHeight()/2);
	}
	else if (condition == "objectPoolSet")
	{
		SceneObject *object = new SceneObject();
		if (OPS || OPSO)
			object = OPS->getObject();
		else
			std::cout << "\n error in Position Actuator, no suitiable Object Pool detected";

		object->setPosX(two->getPosX() + two->getWidth() / 2);
		object->setPosY(two->getPosY() + two->getHeight() / 2);
	}
}

PositionActuator::~PositionActuator()
{
}
