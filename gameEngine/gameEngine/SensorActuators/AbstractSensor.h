#pragma once
class AbstractSensor
{
public:
	AbstractSensor();
	virtual void sense() = 0;
	~AbstractSensor();
};

