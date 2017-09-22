#pragma once
#include "collider.h"
#include "AbstractSprite.h"
#include <iostream>
#include <vector>


class boxCollider : public collider
{
	class SpriteRender;

public:
	boxCollider (AbstractSprite &parent, int w, int h);
	boxCollider(AbstractSprite &parent, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	std::string getType();
	~boxCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	SpriteRender *renderer;
	AbstractSprite *spriteParent;
};

