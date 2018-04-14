#pragma once
#include "AbstractObserver.h"
#include "../Sprite.h"

class CheckBoundsObserver : public AbstractObserver
{
public:
	CheckBoundsObserver(std::string name, void(*f)(Sprite*, int, int), Sprite *s, int w, int h);
	virtual void Notify();


private:
	void(*func_) (Sprite*, int, int);
	Sprite *one;
	int w;
	int h;
};

