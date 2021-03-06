#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "AbstractCollider.h"
#include "../MovingSceneObject.h"
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
	virtual bool collide(AbstractCollider* otherCollider);
	virtual bool collide(AbstractSprite* otherSprite);
	virtual bool getStaticState();
	virtual void Draw(SpriteRenderer &renderer);
	~BoxCollider();

private:
	bool staticState;
	AbstractSprite *spriteParent;
};
#endif