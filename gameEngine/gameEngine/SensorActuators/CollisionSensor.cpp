#include "CollisionSensor.h"

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *first, AbstractSprite *second, bool o) :
	oneS(first), twoS(second), oneShot(o)
{
	this->name = n;
	this->allInScene = false;
	if (oneShot)
		myState = new CollisionSensorSpriteSpriteOneShot(oneS, twoS, actuators);
	else
		myState = new CollisionSensorSpriteSpriteNoOneShot(oneS, twoS, actuators);
}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *s, AbstractCollider *c, bool o) :
	oneS(s), twoC(c), oneShot(o)
{
	this->name = n;
	this->allInScene = false;

	if (oneShot)
		myState = new CollisionSensorSpriteColliderOneShot(oneS, twoC, actuators);
	else
		myState = new CollisionSensorSpriteColliderNoOneShot(oneS, twoC, actuators);
}

CollisionSensor::CollisionSensor(std::string n, AbstractCollider *c1, AbstractCollider *c2, bool o) :
	oneC(c1), twoC(c2), oneShot(o)
{
	this->name = n;
	this->allInScene = false;

	if (oneShot)
		myState = new CollisionSensorColliderColliderOneShot(oneC, twoC, actuators);
	else
		myState = new CollisionSensorColliderColliderNoOneShot(oneC, twoC, actuators);

}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *s1, Scene *sc, bool o) :
	oneS(s1), scene(sc), oneShot(o)
{
	this->name = n;
	this->allInScene = true;
}

void CollisionSensor::sense()
{
	if (myState)
		myState->exec();
	/*
	//if all in scene, check collider for all
	if (allInScene)
	{
		for (int i = 0; i < scene->getColliders().size(); i++)
		{
			//if oneshot set to true, only run act once until sense not true
			bool tapped = true;
			if (tapped)
			{
				if (oneS->collide(scene->getColliders()[i]))
				{
					tapped = false;
					for (int j = 0; j < actuators.size(); j++)
					{
						actuators.at(j)->run();
					}
				}
			}
		}
	}
	
	//if oneshot set to true, only run act once until sense not true
	bool tapped = true;
	if (oneShot)
	{
		if (tapped)
		{
			if (oneS && twoS)
			{
				if (oneS->collide(twoS))
				{
					tapped = false;
					for (int i = 0; i < actuators.size(); i++)
					{
						actuators.at(i)->run();
					}
				
				}
			}
			else if (oneS && twoC)
			{
				if (oneS->collide(twoC))
				{
					tapped = false;
					for (int i = 0; i < actuators.size(); i++)
					{
						actuators.at(i)->run();
					}
				}
			}
			else if (oneC && twoC)
			{
				if (oneC->collide(twoC))
				{
					tapped = false;
					for (int i = 0; i < actuators.size(); i++)
					{
						actuators.at(i)->run();
					}
				}
			}
			//else we are not colliding, reset tapped
			else
			{
				tapped = true;
			}
		}
	}

	//act normally
	else
	{
		if (oneS && twoS)
		{
			myState = new CollisionSensorSpriteSpriteNoOneShot(oneS, twoS, actuators);
			/*if (oneS->collide(twoS))
			{
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
			}
		}
		else if (oneS && twoC)
		{
			if (oneS->collide(twoC))
			{
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
			}
		}
		else if (oneC && twoC)
		{
			if (oneC->collide(twoC))
			{
				for (int i = 0; i < actuators.size(); i++)
				{
					actuators.at(i)->run();
				}
			}
		}
	}
	*/
}

CollisionSensor::~CollisionSensor()
{
}
