#pragma once
#include "AbstractCollider.h"
#include "../ResourceManager.h"

class StaticCircleCollider : public AbstractCollider
{
public:
	StaticCircleCollider(std::string name, float r);
	StaticCircleCollider(std::string name, float r, int posX, int posY);
	virtual int getWidth();
	virtual int getHeight();
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual void Draw(SpriteRenderer &renderer);

private:
	int radius;
	GLfloat transparency;
};

