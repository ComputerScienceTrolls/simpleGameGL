#include "observerhandler.h"
#include <iostream>

ObserverHandler* ObserverHandler::instance = nullptr;

ObserverHandler::ObserverHandler()
{

}

ObserverHandler* ObserverHandler::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ObserverHandler();
    }

    return instance;
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
