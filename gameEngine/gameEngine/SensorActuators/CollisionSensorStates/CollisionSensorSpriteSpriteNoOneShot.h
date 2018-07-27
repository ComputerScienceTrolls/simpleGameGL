#include "CollisionSensorState.h"

class CollisionSensorSpriteSpriteNoOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteSpriteNoOneShot(AbstractSprite* oneSp, AbstractSprite* twoSp, std::vector<AbstractActuator*> acts)
	{
		oneS = oneSp;
		twoS = twoSp;
		actuators = &acts;
	};
	virtual void exec()
	{
		if (oneS->collide(twoS))
		{
			for (int i = 0; i < actuators->size(); i++)
			{
				actuators->at(i)->run();
			}
		}
	};
	~CollisionSensorSpriteSpriteNoOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	std::vector<AbstractActuator*> *actuators;

};