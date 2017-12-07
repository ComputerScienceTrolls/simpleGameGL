#include "ColliderObserver.h"

//takes a function that takes two sprites as parameters, and two sprites to later load to that function
ColliderObserver::ColliderObserver(std::string n, void(*f)(Sprite*, Sprite*), Sprite *S1, Sprite *S2) :
	funcSS_(f), oneS(S1), twoS(S2)
{
	this->name = n;
}

ColliderObserver::ColliderObserver(std::string n, void(*f)(Sprite *, AbstractCollider *), Sprite * S1, AbstractCollider * C2) :
	funcSC_(f), oneS(S1), twoC(C2)
{
	this->name = n;
}

ColliderObserver::ColliderObserver(std::string n, void(*f)(AbstractCollider *, AbstractCollider *), AbstractCollider * C1, AbstractCollider * C2) :
	funcCC_(f), oneC(C1), twoC(C2)
{
	this->name = n;
}

//take the function we got, and pass the two sprites we also got when constructed
void ColliderObserver::Notify()
{
	if (funcCC_)
	{
		this->funcCC_(oneC, twoC);
	}
	else if (funcSC_)
	{
		this->funcSC_(oneS, twoC);
	}
	else
	{
		this->funcSS_(oneS, twoS);
	}
}