#include "PositionActuator.h"

//constructor with a given x and y
PositionActuator::PositionActuator(AbstractSprite *s, int newX, int newY) :
	sprite(s), x(newX), y(newY), condition("both")
{
}

//constructor with a change and condition
PositionActuator::PositionActuator(AbstractSprite *s, int newD, std::string con) :
	sprite(s), d(newD), condition(con)
{
}

//constructor with only a condition
PositionActuator::PositionActuator(AbstractSprite *s, std::string con) :
	sprite(s), condition(con)
{
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
}

PositionActuator::~PositionActuator()
{
}
