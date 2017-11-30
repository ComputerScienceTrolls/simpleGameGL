#pragma once
#include "abstractobserver.h"
#include "../Sprite.h"

class ColliderObserver : public AbstractObserver
{
public:
	ColliderObserver(std::string name, void(*f)(Sprite*, Sprite*), Sprite *s1, Sprite *s2);
	virtual void Notify();

private:
	void(*func_) (Sprite*,Sprite*);
	Sprite *one;
	Sprite *two;
};

