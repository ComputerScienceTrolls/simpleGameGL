#pragma once
#include "AbstractCollider.h"
#include "../AbstractSprite.h"
#include "../AbstractScene.h"
#include "../ResourceManager.h"

#include <iostream>
#include <vector>


class BoxCollider : public AbstractCollider
{

public:
	BoxCollider(std::string name, AbstractSprite &parent, int w, int h);
	BoxCollider(std::string name, AbstractSprite &parent, int w, int h, int posX, int posY);
	BoxCollider(std::string name, AbstractScene &parent, int w, int h);
	BoxCollider(std::string name, AbstractScene &parent, int w, int h, int posX, int posY);
	virtual bool collide(std::vector<AbstractCollider*> otherColliders);
	virtual bool getStaticState();
	virtual glm::vec2 getSpriteCenterPos();
	virtual glm::vec2 getSpritePos();
	virtual glm::vec2 getSpriteSize();
	virtual void Draw(SpriteRenderer &renderer, glm::vec2);
	~BoxCollider();

private:
	bool staticState;
	GLfloat transparency;
	AbstractSprite *spriteParent;
};

