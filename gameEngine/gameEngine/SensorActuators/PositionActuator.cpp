#include "PositionActuator.h"

PositionActuator::PositionActuator(AbstractSprite *s, int newX, int newY) :
	sprite(s), x(newX), y(newY), condition("both")
{
}

PositionActuator::PositionActuator(AbstractSprite *s, int newD, std::string con) :
	sprite(s), d(newD), condition(con)
{
}

PositionActuator::PositionActuator(AbstractSprite *s, std::string con) :
	sprite(s), condition(con)
{
}

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
}

PositionActuator::~PositionActuator()
{
}
