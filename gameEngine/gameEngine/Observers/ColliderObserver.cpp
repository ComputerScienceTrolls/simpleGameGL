#include "ColliderObserver.h"

//takes a function that takes two sprites as parameters, and two sprites to later load to that function
ColliderObserver::ColliderObserver(std::string n, void(*f)(Sprite*, Sprite*), Sprite *S1, Sprite *S2) :
	name(n), func_(f), one(S1), two(S2)
{
}

//take the function we got, and pass the two sprites we also got when constructed
void ColliderObserver::Notify()
{
	this->func_(one, two);
}

void ColliderObserver::setName(std::string newName)
{
	this->name = newName;
}

std::string ColliderObserver::getName()
{
	return this->name;
}
