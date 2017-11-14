#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"

#include "math.h"

class CircleCollider : public AbstractCollider
{

public:
	CircleCollider(std::string name, AbstractSprite &parent, float r);
	CircleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY);
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual float getRadius();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	~circleCollider();

private:
	float radius;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	AbstractSprite *spriteParent;
};

