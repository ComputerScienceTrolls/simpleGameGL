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
