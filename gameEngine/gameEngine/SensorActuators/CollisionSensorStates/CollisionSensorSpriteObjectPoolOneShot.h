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
		actuators = &acts;
	}
	CollisionSensorSpriteObjectPoolOneShot(ObjectPool<SceneObject>* op, AbstractSprite* twoS, std::vector<AbstractActuator*>& acts)
	{
		spr = twoS;
		//objectPool = op;
		//pool = static_cast<std::vector<AbstractSprite*>>(op->getPool());
		std::vector<SceneObject*> temp = op->getPool();
		for (int i = 0; i < temp.size(); i++)
		{
			pool.push_back(dynamic_cast<AbstractSprite*>(temp.at(1)));
		}
		AbstractSprite* test = dynamic_cast<AbstractSprite*>(op->getPool().at(0));
		std::copy(pool.begin(), pool.end(), op->getPool().begin());
		//std::copy(temp.begin(), temp.end(), pool.begin());
		tapped = true;
		std::cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT";
		actuators = &acts;
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
	~CollisionSensorSpriteObjectPoolOneShot() {}

private:
	AbstractSprite *spr;
	//ObjectPool<AbstractSprite> *objectPool;
	std::vector<AbstractSprite*> pool;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};

