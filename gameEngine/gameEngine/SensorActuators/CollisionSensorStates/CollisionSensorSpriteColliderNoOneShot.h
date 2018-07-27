#include "CollisionSensorState.h"

class CollisionSensorSpriteColliderNoOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteColliderNoOneShot(AbstractSprite* oneS, AbstractCollider* twoC, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneS;
		twoC = twoC;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneS->collide(twoC))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteColliderNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractCollider *twoC;
	std::vector<AbstractActuator*> *actuators;
};