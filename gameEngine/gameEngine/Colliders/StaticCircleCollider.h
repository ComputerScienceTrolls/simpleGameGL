#pragma once
#include "AbstractCollider.h"
#include "../ResourceManager.h"

class StaticCircleCollider : public AbstractCollider
{
public:
	StaticCircleCollider(std::string name, float r);
	StaticCircleCollider(std::string name, float r, int posX, int posY);
	virtual float getWidth();
	virtual float getHeight();
	virtual float getRadius();
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual void Draw(SpriteRenderer &renderer, glm::vec2);

private:
	int radius;
	GLfloat transparency;
};

