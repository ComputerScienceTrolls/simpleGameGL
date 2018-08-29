#ifndef ABSTRACTOBSERVER_H
#define ABSTRACTOBSERVER_H

#include <iostream>
#include <string>

class AbstractObserver
{
public:
	AbstractObserver() {};
	virtual void Notify() = 0;
	virtual void setName(std::string);
	virtual std::string getName();
	virtual ~AbstractObserver() {};

protected:
	std::string name;
};

#endif // ABSTRACTOBSERVER_H
