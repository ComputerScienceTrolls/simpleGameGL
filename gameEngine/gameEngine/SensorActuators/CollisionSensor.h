#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "AbstractActuator.h"

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(std::string name, AbstractSprite*, AbstractSprite*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractSprite*, AbstractCollider*, bool oneShot = false);
	CollisionSensor(std::string name, AbstractCollider*, AbstractCollider*, bool oneShot = false);
	void sense();
	~CollisionSensor();

private:
	AbstractSprite *oneS;
	AbstractSprite *twoS;
	AbstractCollider *oneC;
	AbstractCollider *twoC;
	bool oneShot;
};

