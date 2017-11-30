#pragma once
#include "abstractobserver.h"
#include "../Sprite.h"

class CollisionGroupObserver : public AbstractObserver
{
public:
	CollisionGroupObserver(std::string name, void(*f)(Sprite*, std::string), Sprite *s1, std::string s2);
	virtual void Notify();


private:
	void(*func_) (Sprite*, std::string);
	Sprite *one;
	std::string colName;
};
