#include "KeyboardSensor.h"

KeyboardSensor::KeyboardSensor(int k, std::string con) :
	key(k), condition(con)
{
}

void KeyboardSensor::sense()
{
	if (condition == "na")
	{
		if (KeyHandler::getInstance()->Keys[key])
		{
			for (int i = 0; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
		}
	}
	//check only once until released
	else if (condition == "clicked")
	{
		if (KeyHandler::getInstance()->Keys[key] && !oneShot)
		{
			for (int i = 0; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
			oneShot = true;
		}
		else
		{
			if (!KeyHandler::getInstance()->Keys[key])
			{
				oneShot = false;
			}
		}
	}
}

void KeyboardSensor::addActuator(AbstractActuator* act)
{
	actuators.push_back(act);
}

KeyboardSensor::~KeyboardSensor()
{
}
