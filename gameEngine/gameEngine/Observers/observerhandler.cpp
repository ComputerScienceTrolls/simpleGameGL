#include "observerhandler.h"
#include <iostream>

std::auto_ptr<ObserverHandler> ObserverHandler::instance;

ObserverHandler::ObserverHandler()
{
}

ObserverHandler* ObserverHandler::getInstance()
{
    if (instance.get() == nullptr)
    {
        instance.reset(new ObserverHandler());
    }

    return instance.get();
}

void ObserverHandler::addObserver(AbstractObserver &obs)
{
    observers_.insert(&obs);
}

void ObserverHandler::removeObserver(AbstractObserver &obs)
{
    observers_.erase(&obs);
}

void ObserverHandler::NotifyObservers()
{
    std::set<AbstractObserver*>::iterator itr;
    for ( itr = observers_.begin();
          itr != observers_.end(); itr++ )
    (*itr)->Notify();
}

int ObserverHandler::getNumberOfObservers()
{
	return observers_.size();
}

void ObserverHandler::Trigger()
{
    NotifyObservers();
}

ObserverHandler::~ObserverHandler()
{
}
