#pragma once
#include "CollisionSensorState.h"
#include "../../ObjectPool.h"

class CollisionSensorSpriteObjectPoolOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteObjectPoolOneShot(ObjectPool *op, AbstractSprite* twoS, std::vector<AbstractActuator*> &acts)
	{
		spr = twoS;
		objectPool = op;
		tapped = true;
	}
	~CollisionSensorSpriteObjectPoolOneShot();

private:
	AbstractSprite *spr;
	ObjectPool *objectPool;
	bool tapped;
};

