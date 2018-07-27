#include "CollisionSensorState.h"

class CollisionSensorSpriteSceneOneShot : public CollisionSensorState
{
public:
	CollisionSensorSpriteSceneOneShot(AbstractSprite* oneSp, AbstractScene* twoSc, std::vector<AbstractActuator*> &acts)
	{
		oneS = oneSp;
		scene = twoSc;
		actuators = &acts;
		tapped = true;
	};
	virtual void exec()
	{
		for (int i = 0; i < scene->getColliders().size(); i++)
		{
			if (tapped)
			{
				if (oneS->collide(scene->getColliders()[i]))
				{
					tapped = false;
					for (int j = 0; j < actuators->size(); j++)
					{
						actuators->at(j)->run();
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
	~CollisionSensorSpriteSceneOneShot() {};

private:
	AbstractSprite *oneS;
	AbstractScene *scene;
	std::vector<AbstractActuator*> *actuators;
	bool tapped;
};