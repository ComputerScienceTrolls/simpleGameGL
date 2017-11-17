#include "CollisionGroupObserver.h"

CollisionGroupObserver::CollisionGroupObserver(std::string n, void(*f)(Sprite*, std::string), Sprite *S1, std::string S2) :
	func_(f), one(S1), colName(S2)
{
	this->name = n;
}

void CollisionGroupObserver::Notify()
{
	this->func_(one, colName);
}
