#include "CollisionGroupObserver.h"

CollisionGroupObserver::CollisionGroupObserver(void(*f)(Sprite*, std::string), Sprite *S1, std::string S2) :
	func_(f), one(S1), name(S2)
{
}

void CollisionGroupObserver::Notify()
{
	this->func_(one, name);
}
