#ifndef OBSERVER_H
#define OBSERVER_H

#include "abstractobserver.h"

class Observer : public AbstractObserver
{
public:
    Observer(void(*f)());
    virtual void Notify();
	virtual void setName(std::string);
	virtual std::string getName();


private:
   void (*func_) (void);
   std::string name;
};


#endif // OBSERVER_H
