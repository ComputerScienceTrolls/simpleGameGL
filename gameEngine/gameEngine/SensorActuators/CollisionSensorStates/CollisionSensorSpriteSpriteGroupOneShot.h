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
					if (oneS->collide(spriteGroup[i]))
					{
						tapped = false;
						actuators->at(i)->run();
						//since it's a group we don't want to continue checking if one has collided.
						break;
					}
				}
			}
			//else we are not colliding, reset tapped
			else
			{
				tapped = true;
			}
		}
	};
	~CollisionSensorSpriteSpriteGroupOneShot() {};

private:
	AbstractSprite *oneS;
	std::vector<AbstractSprite*> spriteGroup;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};