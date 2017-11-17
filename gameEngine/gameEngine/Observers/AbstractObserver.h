#ifndef ABSTRACTOBSERVER_H
#define ABSTRACTOBSERVER_H

#include <iostream>

class AbstractObserver
{
public:
	virtual void Notify() = 0;
	virtual void setName(std::string) = 0;
	virtual std::string getName() = 0;
};

#endif // ABSTRACTOBSERVER_H
