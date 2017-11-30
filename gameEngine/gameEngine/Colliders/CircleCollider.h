#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"
#include "../ResourceManager.h"

#include "math.h"

class CircleCollider : public AbstractCollider
{

public:
	CircleCollider(std::string name, AbstractSprite &parent, float r);
	CircleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual float getRadius();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpriteSize();
	virtual int getWidth();
	virtual int getHeight();
	virtual void Draw(SpriteRenderer &renderer);
	~CircleCollider();

private:
	float radius;
	GLfloat transparency;
	AbstractSprite *spriteParent;
};

