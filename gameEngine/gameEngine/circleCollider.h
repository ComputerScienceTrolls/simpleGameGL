#pragma once
#include "collider.h"
#include "AbstractSprite.h"

#include "math.h"

class circleCollider : public collider
{

public:
	circleCollider(std::string name, AbstractSprite &parent, float r);
	circleCollider(std::string name, AbstractSprite &parent, float r, int posX, int posY);
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual float getRadius();
	virtual int getPosX();
	virtual int getPosY();
	std::string getType();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	~circleCollider();

private:
	int radius;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	AbstractSprite *spriteParent;
};

