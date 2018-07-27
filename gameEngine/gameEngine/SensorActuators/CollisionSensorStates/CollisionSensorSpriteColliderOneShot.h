#include "CollisionSensorState.h"

class CollisionSensorSpriteColliderOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteColliderOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoC))
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
	~CollisionSensorSpriteColliderOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};