#pragma once
#include "AbstractSensor.h"
#include "../AbstractSprite.h"
#include "AbstractActuator.h"

class CollisionSensor : public AbstractSensor
{
public:
	CollisionSensor(std::string name, AbstractSprite*, AbstractSprite*);
	void sense();
	void addActuator(AbstractActuator*);
	virtual std::string getName();
	virtual void setName(std::string);
	~CollisionSensor();

private:
	AbstractSprite *one;
	AbstractSprite *two;
	std::string name;
	std::vector<AbstractActuator*> actuators;
};

