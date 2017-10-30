#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "AbstractActuator.h"

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(AbstractSprite*, AbstractSprite*);
	void sense();
	void addActuator(AbstractActuator*);
	~CollisionSensor();

private:
	AbstractSprite *one;
	AbstractSprite *two;
	std::vector<AbstractActuator*> actuators;
};

