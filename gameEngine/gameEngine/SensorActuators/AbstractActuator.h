#ifndef ABSTRACTACTUATOR_H
#define ABSTRACTACTUATOR_H

#include <iostream>

class AbstractActuator
{
public:
	AbstractActuator();
	virtual void run() = 0;
	virtual std::string getName();
	virtual void setName(std::string);
	~AbstractActuator();

protected:
	std::string name;
};
#endif

