#pragma once
#include "collider.h"
class circleCollider : public collider
{
	class Sprite;

public:
	circleCollider();
	virtual bool collide(Sprite *sprite);
	~circleCollider();
};

