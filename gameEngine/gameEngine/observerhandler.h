#ifndef OBSERVERHANDLER_H
#define OBSERVERHANDLER_H

#include "abstractobserver.h"
#include "set"

class ObserverHandler
{
public:
    static ObserverHandler* getInstance();
    void addObserver(AbstractObserver &obs);
    void removeObserver(AbstractObserver & obs);
    void NotifyObservers();
    void Trigger();

private:
    ObserverHandler();
    static ObserverHandler* instance;
    std::set<AbstractObserver*> observers_;

};

#endif // OBSERVER_H
