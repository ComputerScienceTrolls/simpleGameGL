#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include "../ResourceManager.h"

#include "math.h"

class CircleCollider : public AbstractCollider, public virtual MovingSceneObject, public virtual DrawSceneObject
{

public:
	CircleCollider(std::string name, AbstractSprite &parent, float r);
	CircleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY);
	CircleCollider(std::string name, AbstractScene &parent, float r);
	CircleCollider(std::string name, AbstractScene &parent, float r, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual bool collide(AbstractCollider* otherCollider);
	virtual bool collide(AbstractSprite* otherSprite);
	virtual float getRadius();
	virtual void Draw(SpriteRenderer &renderer, glm::vec2);
	~CircleCollider();

private:
	float radius;
	AbstractSprite *spriteParent;
};

