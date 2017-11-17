#include "CheckBoundsObserver.h"

CheckBoundsObserver::CheckBoundsObserver(std::string n, void (*f)(Sprite *, int, int), Sprite *s, int width, int height):
	one(s), w(width), h(height)
{
	this->name = n;
}

void CheckBoundsObserver::Notify()
{
	this->func_(one,w,h);
}
