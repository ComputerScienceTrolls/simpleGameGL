#pragma once
#include "Collider.h"
#include "../AbstractSprite.h"
#include <iostream>
#include <vector>


class boxCollider : public collider
{

public:
	boxCollider (std::string name, AbstractSprite &parent, int w, int h);
	boxCollider(std::string name, AbstractSprite &parent, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<collider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual bool getStaticState();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	std::string getType();
	~boxCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	bool staticState;
	AbstractSprite *spriteParent;
};

