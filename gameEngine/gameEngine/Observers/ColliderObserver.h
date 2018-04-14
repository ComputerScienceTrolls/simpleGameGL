#pragma once
#include "AbstractObserver.h"
#include "../Sprite.h"
#include "../Colliders/AbstractCollider.h"

class ColliderObserver : public AbstractObserver
{
public:
	ColliderObserver(std::string name, void(*f)(Sprite*, Sprite*), Sprite *s1, Sprite *s2);
	ColliderObserver(std::string name, void(*f)(Sprite*, AbstractCollider*), Sprite *s1, AbstractCollider *s2);
	ColliderObserver(std::string name, void(*f)(AbstractCollider*, AbstractCollider*), AbstractCollider *s1, AbstractCollider *s2);
	virtual void Notify();

private:
	void(*funcSS_) (Sprite*,Sprite*);
	void(*funcSC_) (Sprite*, AbstractCollider*);
	void(*funcCC_) (AbstractCollider*, AbstractCollider*);
	Sprite *oneS;
	Sprite *twoS;
	AbstractCollider *oneC;
	AbstractCollider *twoC;
};

