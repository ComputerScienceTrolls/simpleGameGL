#include "CollisionSensor.h"

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *first, AbstractSprite *second, bool o) :
	oneShot(o)
{
	this->name = n;
	if (oneShot)
		myState = new CollisionSensorSpriteSpriteOneShot(first, second, actuators);
	else
		myState = new CollisionSensorSpriteSpriteNoOneShot(first, second, actuators);
}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *oneS, std::vector<AbstractSprite*> groupS, bool oneShot)
{
	this->name = n;
	if (oneShot)
		myState = new CollisionSensorSpriteSpriteGroupOneShot(oneS, groupS, actuators);
	else
		myState = new CollisionSensorSpriteSpriteGroupOneShot(oneS, groupS, actuators);
}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *s, AbstractCollider *c, bool o) :
	oneShot(o)
{
	this->name = n;

	if (oneShot)
		myState = new CollisionSensorSpriteColliderOneShot(s, c, actuators);
	else
		myState = new CollisionSensorSpriteColliderNoOneShot(s, c, actuators);
}

CollisionSensor::CollisionSensor(std::string n, AbstractCollider *c1, AbstractCollider *c2, bool o) :
	oneShot(o)
{
	this->name = n;

	if (oneShot)
		myState = new CollisionSensorColliderColliderOneShot(c1, c2, actuators);
	else
		myState = new CollisionSensorColliderColliderNoOneShot(c1, c2, actuators);

}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite *s1, Scene *sc, bool o) :
	oneShot(o)
{
	this->name = n;
}

CollisionSensor::CollisionSensor(std::string n, AbstractSprite* s1, ObjectPoolActuator* opa, bool o) :
	oneShot(o)
{
	this->name = n;
	myState = new CollisionSensorSpriteObjectPoolOneShot(opa, s1, actuators);
	//myState = new 
}

void CollisionSensor::sense()
{
	myState->exec();
}

CollisionSensor::~CollisionSensor()
{
}
