#pragma once
#include "AbstractCollider.h"
#include "../MovingDrawSceneObject.h"
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
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpriteSize();
	virtual float getWidth();
	virtual float getHeight();
	virtual void Draw(SpriteRenderer &renderer, glm::vec2);
	~CircleCollider();

private:
	float radius;
	GLfloat transparency;
	AbstractSprite *spriteParent;
};

