#ifndef BoxColliderAsync_H
#define BoxColliderAsync_H

#include "Colliders/AbstractCollider.h"
#include "MovingSceneObject.h"
#include "AbstractSprite.h"
#include "AbstractScene.h"
#include "ResourceManager.h"

#include <iostream>
#include <vector>

class BoxColliderAsync : public AbstractCollider
{

public:
	BoxColliderAsync(std::string name, AbstractSprite &parent, AbstractCollider*, int w, int h);
	void checkOverlap();
	virtual void Draw(SpriteRenderer &renderer);
	~BoxColliderAsync() {};

	bool overlap;

private:
	bool staticState;
	AbstractSprite *spriteParent;
	AbstractCollider *oc;
};
#endif