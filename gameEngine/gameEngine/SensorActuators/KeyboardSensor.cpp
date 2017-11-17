#include "KeyboardSensor.h"

//constructor, if no condition given, default is "na"
KeyboardSensor::KeyboardSensor(std::string n, int k, std::string con) :
	name(n), key(k), condition(con)
{
}

//sense if given key is pressed, if condition set to clicked only check once per press.
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

//add actuator to run when sensed
void KeyboardSensor::addActuator(AbstractActuator* act)
{
	actuators.push_back(act);
}

void KeyboardSensor::setName(std::string newName)
{
	this->name = newName;
}

std::string KeyboardSensor::getName()
{
	return this->name;
}

KeyboardSensor::~KeyboardSensor()
{
}
