#pragma once
#include "abstractobserver.h"
#include "../Sprite.h"

class ColliderObserver : public AbstractObserver
{
public:
	ColliderObserver(std::string name, void(*f)(Sprite*, Sprite*), Sprite *s1, Sprite *s2);
	virtual void Notify();
	virtual void setName(std::string);
	virtual std::string getName();


private:
	void(*func_) (Sprite*,Sprite*);
	Sprite *one;
	Sprite *two;
	std::string name;
};

