#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "AbstractActuator.h"

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(std::string name, AbstractSprite*, AbstractSprite*);
	void sense();
	~CollisionSensor();

private:
	AbstractSprite *one;
	AbstractSprite *two;
};

