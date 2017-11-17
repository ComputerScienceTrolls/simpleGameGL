#include "ObserverHandler.h"
#include <iostream>

//auto ptr instance of class, when program ends it will delete itself
std::auto_ptr<ObserverHandler> ObserverHandler::instance;

ObserverHandler::ObserverHandler()
{
}

//singleton gets instance if it exists, if not create then return it.
ObserverHandler* ObserverHandler::getInstance()
{
    if (instance.get() == nullptr)
    {
        instance.reset(new ObserverHandler());
    }

    return instance.get();
}

//add an observer to observerhandler, to run later.
void ObserverHandler::addObserver(AbstractObserver &obs)
{
    observers_.insert(&obs);
}

//remove registered observer from observerhandler.
void ObserverHandler::removeObserver(AbstractObserver &obs)
{
    observers_.erase(&obs);
}

//run all observers registered to observer handler.
void ObserverHandler::NotifyObservers()
{
    std::set<AbstractObserver*>::iterator itr;
    for ( itr = observers_.begin();
          itr != observers_.end(); itr++ )
    (*itr)->Notify();
}

//return number of registered observers
int ObserverHandler::getNumberOfObservers()
{
	return observers_.size();
}

ObserverHandler::~ObserverHandler()
{
}
