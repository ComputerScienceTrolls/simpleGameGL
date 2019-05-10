#pragma once
#include "CollisionSensorState.h"
#include "../../ObjectPool.h"
#include "../../AbstractSprite.h"
#include "../AbstractActuator.h"

class CollisionSensorSpriteObjectPoolOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteObjectPoolOneShot(ObjectPool<AbstractSprite> *op, AbstractSprite* twoS, std::vector<AbstractActuator*> &acts)
	{
		spr = twoS;
		//objectPool = op;
		pool = op->getPool();
		tapped = true;
		std::cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT";
	}
	virtual void exec()
	{
		if (tapped)
		{
			for (int i = 0; i < pool.size(); i++)
			{
				if (pool.at(i)->collide(spr))
				{
					tapped = false;
					for (int j = 0; j < actuators->size(); j++)
					{
						actuators->at(j)->run();
					}
				}
			}
		}
		else
		{
			tapped = true;
		}
	}
	~CollisionSensorSpriteObjectPoolOneShot();

private:
	AbstractSprite *spr;
	//ObjectPool<AbstractSprite> *objectPool;
	std::vector<AbstractSprite*> pool;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};

