#ifndef COLLISIONSENSORSTATE_H
#define COLLISIONSENSORSTATE_H

#include "CollisionSensorState"

class CollisionSensorSpriteSceneNoOneShot : public CollisonSensorState
{
public:
	CollisionSensorSpriteSceneNoOneShot(AbstractSprite* oneSp, AbstractScene* twoSc, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		scene = twoSc;
		actuators = &acts;
	};
	virtual void exec()
	{
		for (int i = 0; i < scene->getColliders().size(); i++)
		{
			if (oneS->collide(scene->getColliders()[i]))
			{
				for (int j = 0; j < actuators->size(); j++)
				{
					actuators->at(j)->run();
				}
			}
		}
	};
	~CollisionSensorSpriteSceneNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractScene *scene;
	std::vector<AbstractActuator*> *actuators;
};

#endif