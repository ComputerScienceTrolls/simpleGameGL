#include "TimesActuator.h"

//do something to a sprite after a number of times, example "die" after health decreases to 0.
TimesActuator::TimesActuator(std::string n, AbstractSprite * s, int i, std::string con):
	sprite(s), index(i), condition(con)
{
	this->name = n;
	this->currentIndex = 0;
}

//do something to a sprite after a number of times, example "reset" after a gameover.
TimesActuator::TimesActuator(std::string n, AbstractScene *o, int i,std::string con):
	 mainScene(o), index(i),condition(con)
{
	this->name = n;
	this->currentIndex = 0;
}

//add actuators to be ran after this actuator is activated the defined number of times
void TimesActuator::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}

void TimesActuator::run()
{
	if (mainScene)
	{
		if (condition == "Reset")
		{
			actuators.at(currentIndex)->run();
			currentIndex++;

			if (currentIndex == index)
			{
				mainScene->reset();
				for (int i = index; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
				currentIndex = 0;
			}
		}
	}
	
	else if (sprite)
	{
		if (condition == "Reset")
		{
			actuators.at(currentIndex)->run();
			currentIndex++;

			if (currentIndex == index)
			{
				sprite->reset();

				for (int i = index; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
				currentIndex = 0;
			}
		}
	}
	//if nothing defined, run added actuators
	else
	{
		currentIndex++;
		if (currentIndex == index)
		{
			for (int i = index; i < actuators.size(); i++)
			{
				actuators.at(i)->run();
			}
			currentIndex = 0;
		}
	}
}

TimesActuator::~TimesActuator()
{
}
