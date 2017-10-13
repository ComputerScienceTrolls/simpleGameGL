#include "CheckBoundsObserver.h"

CheckBoundsObserver::CheckBoundsObserver(void(*f)(Sprite *, int, int), Sprite *s, int width, int height):
	one(s), w(width), h(height)
{
}

void CheckBoundsObserver::Notify()
{
	this->func_(one,w,h);
}
