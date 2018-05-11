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
	myState->exec();
}

CollisionSensor::~CollisionSensor()
{
}
