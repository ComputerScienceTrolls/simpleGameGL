#include "KeyboardSensor.h"

KeyboardSensor::KeyboardSensor(int k) :
	key(k)
{
}

void KeyboardSensor::sense()
{
	if (KeyHandler::getInstance()->Keys[key])
	{
		for (int i = 0; i < actuators.size(); i++)
		{
			actuators.at(i)->run();
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
