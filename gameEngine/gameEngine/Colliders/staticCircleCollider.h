#pragma once
#include "collider.h"
class staticCircleCollider : public collider
{
public:
	staticCircleCollider(std::string name, float r);
	staticCircleCollider(std::string name, float r, int posX, int posY);
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual float getRadius();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	virtual std::string getName();

private:
	int radius;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
};

