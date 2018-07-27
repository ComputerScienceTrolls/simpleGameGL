#ifndef COLLISIONSENSORSPRITESPRITEONESHOT_H
#define COLLISIONSENSORSPRITESPRITEONESHOT_H

#include "CollisionSensorState.h"

class CollisionSensorSpriteSpriteOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteSpriteOneShot(AbstractSprite* oneSp, AbstractSprite* twoSp, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		twoS = twoSp;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		if (tapped)
		{
			if (oneS->collide(twoS))
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
	~CollisionSensorSpriteSpriteOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;

};

#endif