#include "Observer.h"
#include <iostream>

Observer::Observer(void(*f)()):
    func_(f)
{

}

void Observer::Notify()
{
    this->func_();
}

void Observer::setName(std::string newName)
{
	this->name = newName;
}

std::string Observer::getName()
{
	return this->name;
}
