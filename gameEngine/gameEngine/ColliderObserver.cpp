#include "ColliderObserver.h"

ColliderObserver::ColliderObserver(void(*f)(Sprite*, Sprite*), Sprite *S1, Sprite *S2) :
	func_(f), one(S1), two(S2)
{
}

void ColliderObserver::Notify()
{
	this->func_(one, two);
}
