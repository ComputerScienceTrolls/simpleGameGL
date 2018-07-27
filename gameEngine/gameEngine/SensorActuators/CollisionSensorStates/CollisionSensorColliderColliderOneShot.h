#ifndef COLLISIONSENSORCOLLIDERCOLLIDERONESHOT_H
#define COLLISIONSENSORCOLLIDERCOLLIDERONESHOT_H

#include "CollisionSensorState.h"

class CollisionSensorColliderColliderOneShot : public CollisionSensorState
{
public:
	CollisionSensorColliderColliderOneShot(AbstractCollider* oneCo, AbstractCollider* twoCo, std::vector<AbstractActuator*> &acts)
	{
		oneC = oneCo;
		twoC = twoCo;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneC->collide(twoC))
			{
				tapped = false;
				for (int i = 0; i < actuators->size(); i++)
				{
					actuators->at(i)->run();
				}
			}
		}
		//else we are not colliding, reset tapped
		else
		{
			tapped = true;
		}
	};
	~CollisionSensorColliderColliderOneShot() {};

private:
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};

#endif