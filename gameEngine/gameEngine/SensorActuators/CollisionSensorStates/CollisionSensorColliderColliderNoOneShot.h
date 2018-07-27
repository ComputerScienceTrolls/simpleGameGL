#ifndef COLLISIONSENSORCOLLIDERCOLLIDERNOONESHOT_H
#define COLLISIONSENSORCOLLIDERCOLLIDER_H

#include "CollisionSensorState.h"

class CollisionSensorColliderColliderNoOneShot : public CollisionSensorState
{
public:
	CollisionSensorColliderColliderNoOneShot(AbstractCollider* oneCo, AbstractCollider* twoCo, std::vector<AbstractActuator*> &acts)
	{
		oneC = oneCo;
		twoC = twoCo;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneC->collide(twoC))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorColliderColliderNoOneShot() {};

private:
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
};

#endif