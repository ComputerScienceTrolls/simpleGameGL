#pragma once
#include <iostream>
class AbstractSensor
{
public:
	AbstractSensor();
	virtual void sense() = 0;
	virtual void setName(std::string) = 0;
	virtual std::string getName() = 0;
	~AbstractSensor();
};

