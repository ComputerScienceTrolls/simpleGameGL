#include "CollisionSensorState.h"

class CollisionSensorSpriteSpriteGroupNoOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteSpriteGroupNoOneShot(AbstractSprite* oneSp, std::vector<AbstractSprite*> sGroup, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		spriteGroup = sGroup;
		actuators = &acts;
	};
	virtual void exec()
	{
		//we are assuming that our sensors are being associated with a actuator with the same index.
		for (int i = 0; i < spriteGroup.size(); i++)
		{
			if (i > actuators->size())
			{
				std::cerr << "sensor/actuator grouping failure, sensor index out of range of actuators";
			}
			else
			{
				if (oneS->collide(spriteGroup[i]))
				{
					actuators->at(i)->run();
					//since it's a group we don't want to continue checking if one has collided.
					break;
				}
			}
		}
	};
	~CollisionSensorSpriteSpriteGroupNoOneShot() {};

private:
	AbstractSprite *oneS;
	std::vector<AbstractSprite*> spriteGroup;
	std::vector<AbstractActuator*> *actuators;
};