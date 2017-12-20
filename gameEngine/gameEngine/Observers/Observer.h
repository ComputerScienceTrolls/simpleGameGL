#ifndef OBSERVER_H
#define OBSERVER_H

#include "abstractobserver.h"

class Observer : public AbstractObserver
{
public:
    Observer(std::string n, void(*f)());
    virtual void Notify();


private:
   void (*func_) (void);
};


#endif // OBSERVER_H
