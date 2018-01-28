#include "TimesActuator.h"


//constructor with a change and condition
TimesActuator::TimesActuator(std::string n, AbstractScene *o, int i,std::string con):
	 mainScene(o), index(i),condition(con)
{
	this->name = n;
	this->currentIndex = 0;
}

void TimesActuator::addActuator(AbstractActuator *act)
{
	actuators.push_back(act);
}


//run based on given or defaulted conditon, if both x and y given assume set to that new pos, if only x or y set it while retaining other not given axis, if flip condition set vertex to negative, always ending up offscreen
void TimesActuator::run()
{
	if (condition == "reset")
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

TimesActuator::~TimesActuator()
{
}
