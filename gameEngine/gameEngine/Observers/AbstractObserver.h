#ifndef ABSTRACTOBSERVER_H
#define ABSTRACTOBSERVER_H

#include <iostream>
#include <string>

class AbstractObserver
{
public:
	virtual void Notify() = 0;
	virtual void setName(std::string);
	virtual std::string getName();

protected:
	std::string name;
};

#endif // ABSTRACTOBSERVER_H
