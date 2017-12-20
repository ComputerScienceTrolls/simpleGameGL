#pragma once
#include "AbstractActuator.h"
#include <iostream>
#include <string>
#include <vector>

class AbstractSensor
{
public:
	AbstractSensor();
	virtual void sense() = 0;
	virtual void setName(std::string);
	virtual std::string getName();
	virtual void addActuator(AbstractActuator*);
	virtual void removeActuator(AbstractActuator*);
	virtual void removeActuator(std::string);
	virtual void removeActuator(int);
	~AbstractSensor();

protected:
	std::string name;
	std::vector<AbstractActuator*> actuators;
};

