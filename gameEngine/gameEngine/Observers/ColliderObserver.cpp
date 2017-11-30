#include "ColliderObserver.h"

//takes a function that takes two sprites as parameters, and two sprites to later load to that function
ColliderObserver::ColliderObserver(std::string n, void(*f)(Sprite*, Sprite*), Sprite *S1, Sprite *S2) :
	func_(f), one(S1), two(S2)
{
	this->name = n;
}

//take the function we got, and pass the two sprites we also got when constructed
void ColliderObserver::Notify()
{
	this->func_(one, two);
}