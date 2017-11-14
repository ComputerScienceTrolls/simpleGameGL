#ifndef OBSERVERHANDLER_H
#define OBSERVERHANDLER_H

#include "abstractobserver.h"
#include "set"
#include <memory>

class ObserverHandler
{
public:
    static ObserverHandler* getInstance();
    void addObserver(AbstractObserver &obs);
    void removeObserver(AbstractObserver & obs);
    void NotifyObservers();
	int getNumberOfObservers();
	~ObserverHandler();

private:
    ObserverHandler();
	static std::auto_ptr<ObserverHandler> instance;
    std::set<AbstractObserver*> observers_;

};

#endif // OBSERVER_H
