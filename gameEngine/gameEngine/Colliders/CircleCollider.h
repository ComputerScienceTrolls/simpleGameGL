#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include "../ResourceManager.h"

class CircleCollider : public AbstractCollider
{

public:
	CircleCollider(std::string name, AbstractSprite &parent, float r);
	CircleCollider(std::string name, AbstractSprite &parent, float r, float posX, float posY);
	CircleCollider(std::string name, AbstractScene &parent, float r);
	CircleCollider(std::string name, AbstractScene &parent, float r, float posX, float posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual bool collide(AbstractCollider* otherCollider);
	virtual bool collide(AbstractSprite* otherSprite);
	virtual float getRadius();
	virtual void Draw(SpriteRenderer &renderer);
	~CircleCollider();

private:
	float radius;
	AbstractSprite *spriteParent;
};

