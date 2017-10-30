#pragma once
class AbstractActuator
{
public:
	AbstractActuator();
	virtual void run() = 0;
	~AbstractActuator();
};

