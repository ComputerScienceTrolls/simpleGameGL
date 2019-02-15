#include "CollisionSensorState.h"

class CollisionSensorSpriteSpriteGroupOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteSpriteGroupOneShot(AbstractSprite* oneSp, std::vector<AbstractSprite*> sGroup, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		spriteGroup = sGroup;
		actuators = &acts;
		tapped = true;
		oneIsHit = false;
	};
	virtual void exec()
	{
		for (int i = 0; i < spriteGroup.size(); i++)
		{
			if (tapped)
			{
				if (i > actuators->size())
				{
					std::cerr << "sensor/actuator grouping failure, sensor index out of range of actuators";
				}
				else
				{
					if (oneS->collide(spriteGroup[i]) && !oneIsHit)
					{
						tapped = false;
						actuators->at(i)->run();
						//since it's a group we don't want to continue checking if one has collided.
						oneIsHit = true;
						tappedCheck = spriteGroup[i];
					}
				}
			}
			//else we are not colliding, check to see if we need to reset tapped
			else
			{
				if (tappedCheck != nullptr)
				{
					if (spriteGroup[i] == tappedCheck)
					{
						//if previous collision is no longer happening set tapped to true so other collisions can activate actuators
						if (!oneS->collide(spriteGroup[i]))
						{
							tapped = true;
						}
					}
				}
			}
		}
		oneIsHit = false;
	};
	~CollisionSensorSpriteSpriteGroupOneShot() {};

private:
	AbstractSprite *oneS;
	std::vector<AbstractSprite*> spriteGroup;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
	bool oneIsHit;
	AbstractSprite *tappedCheck;
};