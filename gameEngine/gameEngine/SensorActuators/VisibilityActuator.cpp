#include "VisibilityActuator.h"

VisibilityActuator::VisibilityActuator(std::string n, AbstractSprite *s, bool b) :
	dso(s), state(b), con("empty"), sprite(NULL)
{
	this->name = n;
}

VisibilityActuator::VisibilityActuator(std::string n, DrawSceneObject* d, bool b):
	dso(d), state(b), con("empty"), sprite(NULL)
{
	this->name = n;
}

VisibilityActuator::VisibilityActuator(std::string n, DrawSceneObject* d, char *str):
	dso(d), state(false), con(str), sprite(NULL)
{
	if (str != "toggle")
	{
		std::cout << "Visibility Actuator " + n + " unreconized condition " + str + "only options for Visibility Actuator at this time: toggle";
	}
	this->name = n;
}

void VisibilityActuator::run()
{
	if (con == "toggle")
	{
		if (dso->getVisible() == false)
			dso->setVisible(true);
		else
			dso->setVisible(false);
	}
	else
	{
		if (state)
		{
			dso->setVisible(true);
		}
		else
		{
			dso->setVisible(false);
		}
	}
}

VisibilityActuator::~VisibilityActuator()
{
}
