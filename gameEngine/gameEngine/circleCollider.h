#pragma once
#include "collider.h"
class circleCollider : public collider
{
	class Sprite;

public:
	circleCollider();
	circleCollider(float r);
	circleCollider(float r, int posX, int posY);
	virtual float getRadius();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	~circleCollider();

private:
	int radius;
	int posXOffset;
	int posYOffset;
	std::string type;
};

