#include "Observer.h"
#include <iostream>

Observer::Observer(std::string n, void(*f)()):
    func_(f)
{
	this->name = n;
}

void Observer::Notify()
{
    this->func_();
}