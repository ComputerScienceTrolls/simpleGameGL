#pragma once
#include "AbstractCollider.h"
#include "../ResourceManager.h"

class StaticCircleCollider : public AbstractCollider
{
public:
	StaticCircleCollider(std::string name, float r);
	StaticCircleCollider(std::string name, float r, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual float getRadius();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	virtual void Draw(SpriteRenderer &renderer);
	virtual std::string getName();

private:
	int radius;
	int posXOffset;
	int posYOffset;
	GLfloat transparency;
	std::string type;
	std::string name;
};

