#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"
#include "../ResourceManager.h"

#include <iostream>
#include <vector>


class BoxCollider : public AbstractCollider
{

public:
	BoxCollider(std::string name, AbstractSprite &parent, int w, int h);
	BoxCollider(std::string name, AbstractSprite &parent, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual bool getStaticState();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual std::string getName();
	virtual void Draw(SpriteRenderer &renderer);
	std::string getType();
	~BoxCollider();

private:
	int offsetH;
	int offsetW;
	int posXOffset;
	int posYOffset;
	std::string type;
	std::string name;
	bool staticState;
	GLfloat transparency;
	AbstractSprite *spriteParent;
};

